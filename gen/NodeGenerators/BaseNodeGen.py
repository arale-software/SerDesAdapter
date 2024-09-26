#*
#* @file SerDesAdapterGen.py
#* @author Sokolov Alexander (a.s.sokolov@arale.ru)
#* @brief Arale SerDesAdapter TScalarNode generator
#* @version 0.1
#* @date 2024-09-09
#*
#* @copyright Copyright (c) 2024
#*

class TBaseNodeGenCPP :
    m_typename = 'TDefaultNode'
    m_typeid = {}
    m_includes = ['/details/TBaseNode.hpp']
    m_in_use = False
    
    def GenerateInclude(self, list, adapterName, needToGenerete) :
        if (needToGenerete == False) :
            for include in self.m_includes : 
                list.append('#include <lib' + adapterName + include + '>')
        needToGenerete = True
        return needToGenerete
    
    def GenerateDefinition(self, list, fieldName, fieldInfo):
        list.append("[ctor] Wrong usage base node generator for " + str(fieldName))
    
    def GenerateInitialization(self, list, fieldName, fieldInfo):
        list.append("[init] Wrong usage base node generator for " + str(fieldName))
        
    def GenerateUpdate(self, list, fieldName, fieldInfo):
        list.append("[update] Wrong usage base node generator for " + str(fieldName))
        