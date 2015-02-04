
--------------------------------
-- @module Armature
-- @extend IAnimatable
-- @parent_module db

--------------------------------
-- 
-- @function [parent=#Armature] getBone 
-- @param self
-- @param #string boneName
-- @return Bone#Bone ret (return value: db.Bone)
        
--------------------------------
-- 
-- @function [parent=#Armature] getAnimation 
-- @param self
-- @return Animation#Animation ret (return value: db.Animation)
        
--------------------------------
-- @overload self, db.Bone, string         
-- @overload self, db.Bone         
-- @function [parent=#Armature] addBone
-- @param self
-- @param #db.Bone bone
-- @param #string parentBoneName

--------------------------------
-- @overload self, string         
-- @overload self, db.Slot         
-- @function [parent=#Armature] removeSlot
-- @param self
-- @param #db.Slot slot

--------------------------------
-- 
-- @function [parent=#Armature] getSlot 
-- @param self
-- @param #string slotName
-- @return Slot#Slot ret (return value: db.Slot)
        
--------------------------------
-- @overload self, string         
-- @overload self, db.Bone         
-- @function [parent=#Armature] removeBone
-- @param self
-- @param #db.Bone bone

--------------------------------
-- 
-- @function [parent=#Armature] replaceSlot 
-- @param self
-- @param #string boneName
-- @param #string oldSlotName
-- @param #db.Slot newSlot
        
--------------------------------
-- 
-- @function [parent=#Armature] getDisplay 
-- @param self
-- @return void#void ret (return value: void)
        
--------------------------------
-- 
-- @function [parent=#Armature] addSlot 
-- @param self
-- @param #db.Slot slot
-- @param #string parentBoneName
        
--------------------------------
-- 
-- @function [parent=#Armature] getSlotByDisplay 
-- @param self
-- @param #void display
-- @return Slot#Slot ret (return value: db.Slot)
        
--------------------------------
-- 
-- @function [parent=#Armature] getBoneByDisplay 
-- @param self
-- @param #void display
-- @return Bone#Bone ret (return value: db.Bone)
        
--------------------------------
-- 
-- @function [parent=#Armature] getArmatureData 
-- @param self
-- @return ArmatureData#ArmatureData ret (return value: db.ArmatureData)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @function [parent=#Armature] invalidUpdate
-- @param self
-- @param #string boneName

--------------------------------
-- 
-- @function [parent=#Armature] getEventDispatcher 
-- @param self
-- @return IEventDispatcher#IEventDispatcher ret (return value: db.IEventDispatcher)
        
--------------------------------
-- 
-- @function [parent=#Armature] sortSlotsByZOrder 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Armature] dispose 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Armature] advanceTime 
-- @param self
-- @param #float passedTime
        
return nil