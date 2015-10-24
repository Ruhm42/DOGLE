#include "DOGLE.hpp"
#include "Script.hpp"

class MyCube : public Script
{
	public:

		MyCube() : Script("MyCube") {}
		Script* 		Clone() { return new MyCube(*this); }

		void			OnDestroy()
		{
			std::cout << " OnDestroy() " << name << " says Boom !" << std::endl;
		}

		void			Update()
		{
			//transform->rotation += glm::vec3(0, 0.002, 0);
		}

		void			OnStop()
		{
			std::cout << "script OnStop() " << std::endl;
		}
	private:

};
