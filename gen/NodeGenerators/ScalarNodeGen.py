#*
#* @file SerDesAdapterGen.py
#* @author Sokolov Alexander (a.s.sokolov@arale.ru)
#* @brief Arale SerDesAdapter TScalarNode generator
#* @version 0.1
#* @date 2024-09-09
#*
#* @copyright Copyright (c) 2024
#*
import NodeGenerators.BaseNodeGen as BaseNodeGen

class TScalarNodeGenCPP(BaseNodeGen.TBaseNodeGenCPP) :
    m_typename = 'TScalarNode'
    m_typeid = {'uint8_t' : 'uint8_t', 'float' : 'float'}
    m_includes = ['/details/TScalarNode.hpp']
    
    def GenerateInclude(self, list, adapterName) :
        TScalarNodeGenCPP.m_in_use = super().GenerateInclude(list, adapterName, TScalarNodeGenCPP.m_in_use)
    
    def GenerateDefinition(self, list, fieldName, fieldInfo):
        typeid = self.m_typeid.get(fieldInfo.get('type'))
        arraySize = str(fieldInfo.get('size'))
        bytesOrder = 'TBaseNode::EBytesOrder::' + str(fieldInfo.get('bytes_order'))
        list.append(str(self.m_typename) + '<' + str(typeid) + '> m_' + str(fieldName) + '{' + bytesOrder + ', ' + arraySize +'};')
        
    def GenerateInitialization(self, list, fieldName, fieldInfo):
        list.append('pos += m_' + str(fieldName) + '.init(reinterpret_cast<uint8_t*>(pInit) + pos);')
        
    def GenerateUpdate(self, list, fieldName, fieldInfo):
        return
        