# include "DOGLE.hpp"
# include "Script.hpp"

	class ControlCamera : public Script
	{
		GameObject* cube = nullptr;

		public:

			ControlCamera() : Script("ControlCamera") {}
			Script* Clone() { return new ControlCamera(*this); }

			void			Awake()
			{
				//transform->position +=  glm::vec3(0,0,-3);
			}
	
			void			Update()
			{
				Navigation();
				PopCube();
				RemoveCube();
				ChangeScene();
				PauseEngine();
				if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				 	Application::singleton->Stop();
				if (Inputs::singleton->KeyDown(GLFW_KEY_Q))
					Application::singleton->Save();
			}

			void			Navigation()
			{
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_A))
				// 	transform->position += glm::vec3(0.05, 0, 0);
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_D))
				// 	transform->position -= glm::vec3(0.05, 0, 0);
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_W))
				// 	transform->position += glm::vec3(0.0, 0.0, 0.05);
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_S))
				// 	transform->position -= glm::vec3(0.0, 0.0, 0.05);
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
				// 	transform->position -= glm::vec3(0.0, 0.05, 0.0);
				// if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
				// 	transform->position += glm::vec3(0.0, 0.05, 0.0);
			}

			void			PopCube()
			{
				if (!cube && Inputs::singleton->KeyDown(GLFW_KEY_E))
					cube = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonTriangle"));
			}

			void			RemoveCube()
			{
				if (cube && Inputs::singleton->KeyDown(GLFW_KEY_R))
				{
					Destroy(cube);
					cube = nullptr;
				}
			}

			void			ChangeScene()
			{
				if (Inputs::singleton->KeyDown(GLFW_KEY_F))
				{
					if (Application::singleton->GetCurrentScene()->name == "Level1")
						Application::singleton->LoadScene("Level2");
					else
						Application::singleton->LoadScene("Level1");
				}
			}

			void		PauseEngine()
			{
				if (Inputs::singleton->KeyDown(GLFW_KEY_P))
					Engine::singleton->Pause();
			}
	};
