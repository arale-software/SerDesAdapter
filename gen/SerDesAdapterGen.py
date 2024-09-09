#*
#* @file SerDesAdapterGen.py
#* @author Sokolov Alexander (a.s.sokolov@arale.ru)
#* @brief Arale SerDesAdapter class generator
#* @version 0.1
#* @date 2024-09-09
#*
#* @copyright Copyright (c) 2024
#*

import json5
import string
import random
import os
from string import Template

#IMPORT HERE YOUR CUSTOM NODE GENERATOR MODULE#
from NodeGenerators import BaseNodeGen as BaseNodeGen
from NodeGenerators import ScalarNodeGen as ScalarNodeGen
from NodeGenerators import CRC8T1NodeGen as CRC8T1NodeGen
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#

def generatorID(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))
    
def TSerdesAdapterClassGenCPP(adapterName, adapterFields):
#DEFINE HERE YOUR CUSTOM NODE GENERATOR CLASS#
    nodeGenerators = [
        BaseNodeGen.TBaseNodeGenCPP(), 
        ScalarNodeGen.TScalarNodeGenCPP(),
        CRC8T1NodeGen.TCRC8T1NodeGenCPP()
        ]    
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#
    adapterIncludes = []
    adapterNodesDefinitions = []
    adapterNodesInitialization = []
    adapterNodesHashTableItems = []
    for fieldName, fieldInfo in adapterFields.items() :
        fieldType = fieldInfo.get('type')
        adapterNodesHashTableItems.append('{"' + str(fieldName) + '",\t\t&m_' + str(fieldName) + '},')
        nodeGenerator = next(gen for gen in nodeGenerators if fieldType in gen.m_typeid)
        nodeGenerator.GenerateInclude(adapterIncludes, adapterName)
        nodeGenerator.GenerateDefinition(adapterNodesDefinitions, fieldName, fieldInfo)
        nodeGenerator.GenerateInitialization(adapterNodesInitialization, fieldName, fieldInfo)
    adapterNodesHashTableItems[-1] = f"{adapterNodesHashTableItems[-1][0: -1]}"
    templateVariables = {
    'class_name': adapterName,
    'header_guard': '__' + adapterName + generatorID() + '__',
    'includes': '\n'.join(adapterIncludes),
    'nodes_definitions': '\n\t'.join(adapterNodesDefinitions),
    'nodes_init': '\n\t\t'.join(adapterNodesInitialization),
    'hash_table_items': '\n\t\t'.join(adapterNodesHashTableItems),
    }            
    with open(os.getcwd()+'/AdapterTemplates/AdapterTemplateCPP.in', 'r') as templateFile:
        src = Template(templateFile.read())
        result = src.substitute(templateVariables)
        print(result) #TODO gen class

with open("packet.json5", "r+") as resultsFile: #TODO arg file
    jsonData = json5.load(resultsFile, allow_duplicate_keys=False)
    adapterInfo = jsonData.get('SerDesAdapter')
    adapterName = adapterInfo.get('Name')
    adapterFields = adapterInfo.get('Fields')
    TSerdesAdapterClassGenCPP(adapterName, adapterFields)