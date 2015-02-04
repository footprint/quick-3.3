
--------------------------------
-- @module DBCCFactory
-- @extend BaseFactory
-- @parent_module db

--------------------------------
-- 
-- @function [parent=#DBCCFactory] hasDragonBones 
-- @param self
-- @param #string skeletonName
-- @param #string armatureName
-- @param #string animationName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#DBCCFactory] loadTextureAtlas 
-- @param self
-- @param #string textureAtlasFile
-- @param #string name
-- @return ITextureAtlas#ITextureAtlas ret (return value: db.ITextureAtlas)
        
--------------------------------
-- 
-- @function [parent=#DBCCFactory] refreshAllTextureAtlasTexture 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#DBCCFactory] refreshTextureAtlasTexture 
-- @param self
-- @param #string name
        
--------------------------------
-- 
-- @function [parent=#DBCCFactory] loadDragonBonesData 
-- @param self
-- @param #string dragonBonesFile
-- @param #string name
-- @return DragonBonesData#DragonBonesData ret (return value: db.DragonBonesData)
        
--------------------------------
-- 
-- @function [parent=#DBCCFactory] getInstance 
-- @param self
-- @return DBCCFactory#DBCCFactory ret (return value: db.DBCCFactory)
        
--------------------------------
-- @overload self, string, string         
-- @overload self, string         
-- @overload self, string, string, string, string, string         
-- @function [parent=#DBCCFactory] buildArmature
-- @param self
-- @param #string armatureName
-- @param #string skinName
-- @param #string animationName
-- @param #string dragonBonesName
-- @param #string textureAtlasName
-- @return DBCCArmature#DBCCArmature ret (return value: db.DBCCArmature)

--------------------------------
-- 
-- @function [parent=#DBCCFactory] DBCCFactory 
-- @param self
        
return nil
