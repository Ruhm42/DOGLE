#include "Builder.hpp"

// CONSTRUCTOR DESTRUCTOR //

Builder::Builder()
{
	_app = nullptr;
	_scene = nullptr;
	_go = nullptr;

	if (_token.empty())
	{
		_token.push_back(std::make_pair("APPLICATION:", &Builder::_ParseApplication));
		_token.push_back(std::make_pair("PREFAB:", &Builder::_ParsePrefab));
		_token.push_back(std::make_pair("GAMEOBJECT:", &Builder::_ParseGameObject));
		_token.push_back(std::make_pair("SCENE:", &Builder::_ParseScene));
		_token.push_back(std::make_pair("TRANSFORM:", &Builder::_ParseTransform));
		_token.push_back(std::make_pair("CAMERA:", &Builder::_ParseCamera));
		_token.push_back(std::make_pair("SCRIPT:", &Builder::_ParseScript));
		_token.push_back(std::make_pair("SKIN:", &Builder::_ParseSkin));
	}

	ScriptFactory::Register("ControlCamera", new ControlCamera);
	ScriptFactory::Register("MyCube", new MyCube);
	ScriptFactory::Register("ScriptTriangle", new ScriptTriangle);
}

Builder::~Builder(void)
{
}

// OVERLOADS //


// PUBLIC //

Application*	Builder::Build(std::string file)
{
	std::string line;
	std::ifstream myfile (file);
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
			_ParseLine(line);
		myfile.close();
	}
	else 
		throw DError() << msg("Build() failed. " + file + " cannot be found."); 
	if (_go && _scene)
	{
		_scene->AddGameObject(_go);
		_app->AddScene(_scene);
	}
	return _app;
}

// PRIVATE //

void			Builder::_ParseLine(std::string& line)
{
	if (line.size() == 0 || line[0] == '#')
		return ;
	for (std::size_t i = 0; i < _token.size(); i++)
	{
		if ((line.find( _token[i].first )) != std::string::npos)
		{
			std::string str(line.c_str() + (line.find(":") + 1));
			(this->*_token[i].second)(str);
			return ;
		}
	}
	throw DError() << msg("Parsing stop. No registered token found with line : \n" + line);
}

void			Builder::_ParseApplication(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 3);
	
	_app = new Application(attributs[0], stoi(attributs[1]), stoi(attributs[2]));
	
	delete[] attributs;
}

void			Builder::_ParsePrefab(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 1);
	
	if (_go != nullptr)
		_app->AddPrefab(_go);
	_go = new GameObject(attributs[0]);

	delete[] attributs;
}

void			Builder::_ParseGameObject(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 1);
	
	if (_go != nullptr)
		_scene->AddGameObject(_go);
	_go = new GameObject(attributs[0]);
	_go->SetIsPrefab(false);

	delete[] attributs;
}

void			Builder::_ParseScene(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 1);

	if (_go)
	{
		if (_scene == nullptr)
		{
			_app->AddPrefab(_go);
			_go = nullptr;
		}
		else
		{
			_scene->AddGameObject(_go);	
			_go = nullptr;		
		}

	}
	if (_scene != nullptr)
		_app->AddScene(_scene);
	_scene = new Scene(attributs[0]);
	
	delete[] attributs;
}

void			Builder::_ParseTransform(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 3);

	Transform t(_AttributToVec3(attributs[0]), _AttributToVec3(attributs[1]), _AttributToVec3(attributs[2]));
	*(_go->GetComponent<Transform>()) = t;

	delete[] attributs;
}

void			Builder::_ParseCamera(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 3);

	_go->AddComponent( new Camera(stof(attributs[0]), stof(attributs[1]), stof(attributs[2])) );

	delete[] attributs;
}

void			Builder::_ParseScript(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 1);

	_go->AddComponent( factoryS.Create(attributs[0]) );

	delete[] attributs;
}

void			Builder::_ParseSkin(std::string& line)
{
	std::string	*attributs;
	attributs = _GetAttributs(line, 1);

	_go->AddComponent( new Skin(attributs[0]) );

	delete[] attributs;
}



std::string*	Builder::_GetAttributs(std::string& line, int count)
{
	std::istringstream ss(line);
	std::string*	attributs = new std::string[count];
	
	for(int i=0; i < count; i++)
		std::getline(ss, attributs[i], SEPARATOR);
	
	return attributs;
}

Vector3f		Builder::_AttributToVec3(std::string& attribut)
{
	Vector3f	vector;
	std::istringstream ss(attribut);
	std::string	value[3];

	for(int i=0; i < 3; i++)
		std::getline(ss, value[i], SEPARATOR_F);

	vector.x = stof(value[0]);
	vector.y = stof(value[1]);
	vector.z = stof(value[2]);
	return vector;
}

// GETTER SETTER //
