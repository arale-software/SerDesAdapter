#*
#* @file SerDesAdapterGen.py
#* @author Sokolov Alexander (a.s.sokolov@arale.ru)
#* @brief Arale SerDesAdapter class generator
#* @version 0.1
#* @date 2024-09-09
#*
#* @copyright Copyright (c) 2024
#*

# pip install pandas openpyxl xlrd

import csv
import json5
import pandas as pd
import ast
import argparse
import string
import random
import os
from string import Template
from pathlib import Path
import shutil 
import importlib
import inspect

def loadNodeGenerators():
    """
    Автоматически загружает и создает экземпляры всех генераторов узлов
    из директории NodeGenerators
    """
    files = os.listdir('NodeGenerators')
    moduleNames = [f[:-3] for f in files if f.endswith('.py') and not f.startswith('_')]
    importedModules = {}
    for moduleName in moduleNames:
        try:
            module = importlib.import_module(f'NodeGenerators.{moduleName}')
            importedModules[moduleName] = module
        except Exception as e:
            print(f"Ошибка при импорте модуля {moduleName}: {e}")
    def findCppClass(module):
        for name, obj in inspect.getmembers(module):
            if inspect.isclass(obj) and name.endswith('NodeGenCPP'):
                return obj
        return None
    nodeGenerators = []
    for moduleName, module in importedModules.items():
        cppClass = findCppClass(module)
        if cppClass:
            try:
                instance = cppClass()
                nodeGenerators.append(instance)
            except Exception as e:
                print(f"Ошибка при создании экземпляра класса {cppClass.__name__}: {e}")
    return nodeGenerators

def generatorID(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))
    
def TSerdesAdapterClassGenCPP(adapterName, adapterFields):
    nodeGenerators = loadNodeGenerators()
    adapterIncludes = []
    adapterNodesDefinitions = []
    adapterNodesInitialization = []
    adapterNodesUpdate = []
    adapterNodesHashTableItems = []
    for fieldName, fieldInfo in adapterFields.items() :
        fieldType = fieldInfo.get('type')
        adapterNodesHashTableItems.append('{"' + str(fieldName) + '",\t\t&m_' + str(fieldName) + '},')
        nodeGenerator = next(gen for gen in nodeGenerators if fieldType in gen.m_typeid)
        nodeGenerator.GenerateInclude(adapterIncludes, adapterName)
        nodeGenerator.GenerateDefinition(adapterNodesDefinitions, fieldName, fieldInfo)
        nodeGenerator.GenerateInitialization(adapterNodesInitialization, fieldName, fieldInfo)
        nodeGenerator.GenerateUpdate(adapterNodesUpdate, fieldName, fieldInfo)
    adapterNodesHashTableItems[-1] = f"{adapterNodesHashTableItems[-1][0: -1]}"
    templateVariables = {
    'class_name': adapterName,
    'header_guard': '__' + adapterName + generatorID() + '__',
    'includes': '\n'.join(adapterIncludes),
    'nodes_definitions': '\n\t'.join(adapterNodesDefinitions),
    'nodes_init': '\n\t\t'.join(adapterNodesInitialization),
    'nodes_update': '\n\t\t'.join(adapterNodesUpdate),
    'hash_table_items': '\n\t\t'.join(adapterNodesHashTableItems),
    }            
    with open(os.getcwd()+'/AdapterTemplates/AdapterTemplateCPP.in', 'r') as AdapterTemplateCPP,\
         open(os.getcwd()+'/AdapterTemplates/AdapterTemplateLibCPP.in', 'r') as AdapterTemplateLibCPP,\
         open(os.getcwd()+'/AdapterTemplates/CMakeLists.in', 'r') as CMakeTemplateFile:
        adapterSrc = Template(AdapterTemplateCPP.read())
        adapterLibSrc = Template(AdapterTemplateLibCPP.read())
        cmakeSrc = Template(CMakeTemplateFile.read())
        adapterFileData = adapterSrc.substitute(templateVariables)
        adapterLibFileData = adapterLibSrc.substitute(templateVariables)
        cmakeFileData = cmakeSrc.substitute(templateVariables)
        thirdPartyIncludes = os.getcwd()+'/SourceCPP/third_party'
        detailsIncludes = os.getcwd()+'/SourceCPP/details'
        adapterDirectory = os.getcwd()+'/' + adapterName + '/src'
        adapterLibDirectory = adapterDirectory +'/lib/lib' + adapterName
        shutil.copytree(thirdPartyIncludes, adapterDirectory + '/third_party') 
        shutil.copytree(detailsIncludes, adapterLibDirectory + '/details') 
            
        with open(adapterLibDirectory + '/' + adapterName + '.hpp', 'a') as adapterFile,\
             open(adapterLibDirectory + '/' + adapterName + '.cpp', 'a') as adapterLibFile,\
             open(os.getcwd()+'/' + adapterName+ '/CMakeLists.txt', 'a') as cmakeFile:
            print(adapterFileData, file=adapterFile)
            print(adapterLibFileData, file=adapterLibFile) 
            print(cmakeFileData, file=cmakeFile) 



def parseJson5(filePath):
    with open(filePath, 'r', encoding='utf-8') as file:
        data = json5.load(file, allow_duplicate_keys=False)
        return data

def parseCsv(filePath):
    fields = {}
    with open(filePath, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        columns = [col for col in reader.fieldnames if col != 'Fields']
        
        for row in reader:
            fieldName = row['Fields']
            fields[fieldName] = {}
            
            for col in columns:
                try:
                    value = ast.literal_eval(row[col])
                except (ValueError, SyntaxError):
                    value = row[col]
                fields[fieldName][col] = value
    return fields

def parseXls(filePath):
    try:
        df = pd.read_excel(filePath, sheet_name=0)
        fields = {}  
        for _, row in df.iterrows():
            fieldName = row['Fields']        
            fieldData = {}
            for col in df.columns:
                if col != 'Fields':
                    try:
                        value = pd.to_numeric(row[col])
                    except ValueError:
                        value = row[col]
                    if isinstance(value, str):
                        try:
                            value = ast.literal_eval(value)
                        except (ValueError, SyntaxError):
                            pass
                    
                    fieldData[col] = value
            
            fields[fieldName] = fieldData
        return fields
    except Exception as e:
        raise ValueError(f"Can't read Excel file: {str(e)}")

def main():
    parser = argparse.ArgumentParser(description='SerDesAdapter 1.0 alpha')
    parser.add_argument('--filename', type=str, help='File for serialization')
    parser.add_argument('--classname', type=str, help='Adapter class name (optional)') #or filename
    args = parser.parse_args()
    filePath = Path(args.filename)
    try:
        if filePath.suffix.lower() == '.json5':
            parsedData = parseJson5(filePath)
        elif filePath.suffix.lower() == '.csv':
            parsedData = parseCsv(filePath)
        elif filePath.suffix.lower() in ('.xls', '.xlsx'):
            parsedData = parseXls(filePath)
        else:
            raise ValueError("Wrong file format (wanted .json5, .csv, .xls, .xlsx)")
        if args.classname:
            adapterName = args.classname
        else:
            adapterName = filePath.stem           
        TSerdesAdapterClassGenCPP(adapterName, parsedData)    
    except FileNotFoundError:
        print(f"Error: file {filePath} not found")
    except Exception as e:
        print(f"Error: {str(e)}")

if __name__ == '__main__':
    main()