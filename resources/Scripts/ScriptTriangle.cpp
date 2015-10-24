# include "DOGLE.hpp"
# include "Script.hpp"

	class ScriptTriangle : public Script
	{
		public:

			ScriptTriangle() : Script("ScriptTriangle") {}
			Script* Clone() { return new ScriptTriangle(*this); }

			void			Awake()
			{
				//transform->position = (Camera::GetMainCamera()->GetComponent<Camera>()->transform->position * glm::vec3(-1,-1,-1)) + glm::vec3(0,0,-2);
			}

	};
