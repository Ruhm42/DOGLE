#ifndef BUILDER_HPP
# define BUILDER_HPP

# include "DOGLE.hpp"
# include "SCRIPTS.hpp"
# include "Script.hpp"
# include "Application.hpp"
# include "Skin.hpp"
# include "ScriptFactory.hpp"

	class Builder
	{
		typedef void	(Builder::*funcPtr)(std::string&);

		public:
			Builder(void);
			~Builder(void);
			Application*	Build(std::string file);

			ScriptFactory	factoryS;

		private:
			std::vector< std::pair<std::string, funcPtr> >		_token;

			Builder &operator=(Builder const &rhs);
			Builder(Builder const &src);
			void		_ParseLine(std::string& line);

			void		_ParseApplication(std::string& line);
			void		_ParsePrefab(std::string& line);
			void		_ParseGameObject(std::string& line);
			void		_ParseScene(std::string& line);
			void		_ParseTransform(std::string& line);
			void		_ParseCamera(std::string& line);
			void		_ParseScript(std::string& line);
			void		_ParseSkin(std::string& line);

			std::string*	_GetAttributs(std::string& line, int count);
			Vector3f		_AttributToVec3(std::string& attribut);

			Application*	_app;
			Scene*			_scene;
			GameObject*		_go;
	};

#endif
