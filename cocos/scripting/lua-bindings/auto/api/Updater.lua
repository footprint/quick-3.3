
--------------------------------
-- @module Updater
-- @extend Ref
-- @parent_module cc

--------------------------------
--  @brief Register script handler, the hander will receive messages
-- @function [parent=#Updater] registerScriptHandler 
-- @param self
-- @param #int handler
        
--------------------------------
-- 
-- @function [parent=#Updater] removeDirectory 
-- @param self
-- @param #char path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, cc.__Array         
-- @overload self, char, char, char, bool         
-- @overload self, char, char         
-- @overload self, char         
-- @function [parent=#Updater] update
-- @param self
-- @param #char zipUrl
-- @param #char zipFile
-- @param #char unzipTmpDir
-- @param #bool resetBeforeUnZIP

--------------------------------
-- 
-- @function [parent=#Updater] unregisterScriptHandler 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Updater] query 
-- @param self
-- @param #char updateUrl
        
--------------------------------
-- 
-- @function [parent=#Updater] createDirectory 
-- @param self
-- @param #char path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  @brief Sets connection time out in seconds
-- @function [parent=#Updater] setConnectionTimeout 
-- @param self
-- @param #unsigned int timeout
        
--------------------------------
--  @brief Gets connection time out in secondes
-- @function [parent=#Updater] getConnectionTimeout 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#Updater] Updater 
-- @param self
        
return nil
