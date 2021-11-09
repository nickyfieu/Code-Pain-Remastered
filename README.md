# Code-Pain-Remastered
  Personal "engine"/sandbox for learning new topics such as ECS, Data Oriented Programming, indepth look at DirectX and or other graphics API's.

  Created by Nicky Fieu.<br/>
  > ***[Porfolio Website](https://nickyfieu.myportfolio.com/work)***<br/>
  > ***[LinkedIn](https://www.linkedin.com/in/nicky-f-986552195/)***<br/>
  > ***[Resume](https://nickyfieu.myportfolio.com/resume)***<br/>
## ECS - Data Oriented Programming
  Data oriented programming and making an entity component system is something I have been wanting to try out after hearing the term from friends and other programmers. <br/>
  Learning resources:<br/>
  -***[CppCon 2014: Mike Acton "Data-Oriented Design and C++"](https://www.youtube.com/watch?v=rX0ItVEVjHc)***<br/>
  -***[Understanding data-oriented design for entity component systems - Unity at GDC 2019](https://www.youtube.com/watch?v=0_Byw9UMn9g)***<br/>
  -***[code::dive conference 2014 - Scott Meyers: Cpu Caches and Why You Care](https://www.youtube.com/watch?v=WDIkqP4JbkE)***<br/>
  -***[A SIMPLE ENTITY COMPONENT SYSTEM by Austin Morlan](https://austinmorlan.com/posts/entity_component_system/#the-component-array)***<br/>

  My entity component system is based on Austin Morlan's entity component system.<br/><br/>
  Where my ecs differs is that:<br/>
  - I use less memory to get a new entity index<br/>
  - Instead of using 2 unodered maps in the component manager, I opted for 3 arrays.<br/>