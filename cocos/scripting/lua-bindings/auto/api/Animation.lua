
--------------------------------
-- @module Animation
-- @parent_module db

--------------------------------
-- 
-- @function [parent=#Animation] getAnimationList 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#Animation] setTimeScale 
-- @param self
-- @param #float timeScale
        
--------------------------------
-- 
-- @function [parent=#Animation] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Animation] clear 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Animation] dispose 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Animation] play 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Animation] hasAnimation 
-- @param self
-- @param #string animationName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Animation] getLastAnimationState 
-- @param self
-- @return AnimationState#AnimationState ret (return value: db.AnimationState)
        
--------------------------------
-- 
-- @function [parent=#Animation] gotoAndPlay 
-- @param self
-- @param #string animationName
-- @param #float fadeInTime
-- @param #float duration
-- @param #int playTimes
-- @param #int layer
-- @param #string group
-- @param #int fadeOutMode
-- @param #bool pauseFadeOut
-- @param #bool pauseFadeIn
-- @return AnimationState#AnimationState ret (return value: db.AnimationState)
        
--------------------------------
-- 
-- @function [parent=#Animation] getState 
-- @param self
-- @param #string name
-- @param #int layer
-- @return AnimationState#AnimationState ret (return value: db.AnimationState)
        
--------------------------------
-- 
-- @function [parent=#Animation] getIsComplete 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Animation] advanceTime 
-- @param self
-- @param #float passedTime
        
--------------------------------
-- 
-- @function [parent=#Animation] getIsPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Animation] gotoAndStop 
-- @param self
-- @param #string animationName
-- @param #float time
-- @param #float normalizedTime
-- @param #float fadeInTime
-- @param #float duration
-- @param #int layer
-- @param #string group
-- @param #int fadeOutMode
-- @return AnimationState#AnimationState ret (return value: db.AnimationState)
        
--------------------------------
-- 
-- @function [parent=#Animation] getTimeScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Animation] Animation 
-- @param self
        
return nil
