# LearnOpenGL

  这是一个迷你版3D图形引擎，暂时没有添加gui库，使用premake5构建visual studio项目，运行GenerateProj.bat即可构建(暂时未用其它电脑测试)
  
  事件系统，层级系统，引擎大致架构均模仿Hazel引擎
  
  渲染器类以及相关高级对象类是自主实现
  
  目前采用即时渲染的模式，Renderer3D类的主要渲染接口为
  BeginScene(),
  
  Submit(Mesh& mesh,Material& material,glm::mat4 transform)，
  
  EndScene()

  <img width="964" height="687" alt="e5723222c1f893711fb66df9a7c6b0a9" src="https://github.com/user-attachments/assets/9285bd8d-d53e-49a1-88f4-6fc307fa8127" />

  目前尚未构建场景类(Scene)，实体组件系统(ECS)，资源管理器(Assets Manager),相关对象以及逻辑暂时交给ExampleLayer处理

  有机会将在未来创建editor界面
