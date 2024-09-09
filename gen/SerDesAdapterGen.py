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
from string import Template

from numpy import False_


def generatorID(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

class NodeInfo :
    m_typename = 'TDefaultNode'
    m_typeid = {'CRC8T1' : 'void'}
    m_includes = ['/details/TBaseNode.hpp']
    m_in_use = False
    def GenerateInclude(self, list, adapterName) :
        if self.m_in_use == False :
            for include in self.m_includes : 
                list.append('#include <' + adapterName + include)
            self.m_in_use = True
    def GenerateDefinition(self, list, fieldName, fieldInfo):
        typeid = self.m_typeid.get(fieldInfo.get('type'))
        list.append(str(self.m_typename) + '<' + str(typeid) + '> m_' + str(fieldName) + '{' + str(fieldInfo.get('bytes_order')) + ', ' + str(fieldInfo.get('size'))+'};')
    def GenerateInitialization(self, list, fieldName, fieldInfo):
        typeid = self.m_typeid.get(fieldInfo.get('type'))
        list.append('pos += m_' + str(fieldName) + '.init(reinterpret_cast<' + str(typeid) + '*>(pInit) + pos);')
    
        
class TScalarNode(NodeInfo) :
    m_typename = 'TScalarNode'
    m_typeid = {'uint8_t' : 'uint8_t', 'float' : 'float'}
    m_includes = ['/details/TScalarNode.hpp']


def TSerdesAdapterClassGen(adapterName, adapterFields):
    scalarNodeInfo = TScalarNode()
    defaultNodeInfo = NodeInfo()
    scalarTypes = ["uint8_t","float"]
    defaultTypes = ["CRC8T1"]
    adapterIncludes = []
    adapterNodesDefinitions = []
    adapterNodesInitialization = []
    adapterNodesHashTableItems = []
    for fieldName, fieldInfo in adapterFields.items() :
        fieldType = fieldInfo.get('type')
        adapterNodesHashTableItems.append('{"' + str(fieldName) + '",\t\t&m_' + str(fieldName) + '},')
        #TODO del last ,
        if scalarTypes.count(fieldType) :
            scalarNodeInfo.GenerateInclude(adapterIncludes, adapterName)
            scalarNodeInfo.GenerateDefinition(adapterNodesDefinitions, fieldName, fieldInfo)
            scalarNodeInfo.GenerateInitialization(adapterNodesInitialization, fieldName, fieldInfo)
        elif defaultTypes.count(fieldType) :
            defaultNodeInfo.GenerateInclude(adapterIncludes, adapterName)
            defaultNodeInfo.GenerateDefinition(adapterNodesDefinitions, fieldName, fieldInfo)
            defaultNodeInfo.GenerateInitialization(adapterNodesInitialization, fieldName, fieldInfo)
    d = {
    'class_name': adapterName,
    'header_guard': '__' + adapterName + generatorID() + '__',
    'includes': '\n'.join(adapterIncludes),
    'nodes_definitions': '\n\t'.join(adapterNodesDefinitions),
    'nodes_init': '\n\t\t'.join(adapterNodesInitialization),
    'hash_table_items': '\n\t\t'.join(adapterNodesHashTableItems),
    }            
    with open('AdapterTemplate.in', 'r') as f:
        src = Template(f.read())
        result = src.substitute(d)
        print(result)

with open("packet.json5", "r+") as resultsFile:
    jsonData = json5.load(resultsFile, allow_duplicate_keys=False)
    adapterInfo = jsonData.get('SerDesAdapter')
    adapterName = adapterInfo.get('Name')
    adapterFields = adapterInfo.get('Fields')
    TSerdesAdapterClassGen(adapterName, adapterFields)
    