
--------------------------------
-- @module DBCCArmatureNode
-- @extend Node,IAnimatable
-- @parent_module db

--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] getAnimation 
-- @param self
-- @return Animation#Animation ret (return value: db.Animation)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] registerMovementEventHandler 
-- @param self
-- @param #int func
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] getCCEventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher ret (return value: cc.EventDispatcher)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] registerFrameEventHandler 
-- @param self
-- @param #int func
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] getArmature 
-- @param self
-- @return DBCCArmature#DBCCArmature ret (return value: db.DBCCArmature)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] unregisterMovementEventHandler 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] unregisterFrameEventHandler 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] initWithDBCCArmature 
-- @param self
-- @param #db.DBCCArmature armature
-- @param #db.WorldClock clock
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] getCCDisplay 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] advanceTime 
-- @param self
-- @param #float dt
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] create 
-- @param self
-- @param #db.DBCCArmature armature
-- @return DBCCArmatureNode#DBCCArmatureNode ret (return value: db.DBCCArmatureNode)
        
--------------------------------
-- create DDCCArmatureNode with WorldClock<br>
-- param armature<br>
-- param clock if null, use WorldClock::getInstance()<br>
-- return 
-- @function [parent=#DBCCArmatureNode] createWithWorldClock 
-- @param self
-- @param #db.DBCCArmature armature
-- @param #db.WorldClock clock
-- @return DBCCArmatureNode#DBCCArmatureNode ret (return value: db.DBCCArmatureNode)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] update 
-- @param self
-- @param #float dt
        
--------------------------------
-- 
-- @function [parent=#DBCCArmatureNode] DBCCArmatureNode 
-- @param self
        
return nil
