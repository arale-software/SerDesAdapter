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

class TCRC8T1NodeGenCPP(BaseNodeGen.TBaseNodeGenCPP) :
    m_typename = 'TCRC8T1Node'
    m_typeid = {'CRC8T1' : 'uint8_t'}
    m_includes = ['/details/TCRC8T1Node.hpp']

    def GenerateInclude(self, list, adapterName) :
        TCRC8T1NodeGenCPP.m_in_use = super().GenerateInclude(list, adapterName, TCRC8T1NodeGenCPP.m_in_use) #FIXME

    def GenerateDefinition(self, list, fieldName, fieldInfo):
        polyCRC = hex(fieldInfo.get('polyCRC'))
        initCRC = hex(fieldInfo.get('initCRC'))
        bytesOrder = 'TBaseNode::EBytesOrder::' + str(fieldInfo.get('bytes_order'))
        list.append(str(self.m_typename) + ' m_' + str(fieldName) + '{' + polyCRC + ', ' + initCRC + ', ' + bytesOrder + '};')

    def GenerateInitialization(self, list, fieldName, fieldInfo):
        begin = str(fieldInfo.get('begin'))
        end = str(fieldInfo.get('end'))
        list.append('pos += m_' + str(fieldName) + '.init(reinterpret_cast<uint8_t*>(pInit) + pos, &m_' + begin + ', &m_' + end + ');')
        