#include "Transform.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Transform::Transform()
{
	std::cout << "construct Transform " << std::endl;
	position = Vector3f(0.0, 0.0, 0.0);
	rotation = Vector3f(0.0f);
	scale = Vector3f(1.0f);
}

Transform::Transform(Vector3f pos, Vector3f rot, Vector3f sc)
{
	position = pos;
	rotation = rot;
	scale = sc;	
}


Transform::Transform(Transform const & src)
{
	std::cout << "construct Transform " << std::endl;
	*this = src;
}

Transform::~Transform(void)
{
	std::cout << "destruct Transform" << std::endl;
}

// OVERLOADS //

Transform		&Transform::operator=(Transform const & rhs)
{
	position = rhs.position; 
	rotation = rhs.rotation;
	scale = rhs.scale;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Transform const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Transform::CalculateTransform()
{ 
	// _local = Matrix4f(1.0);
	// _local = glm::rotate(_local, rotation.x, Vector3f(1.0f, 0.0f, 0.0f));
	// _local = glm::rotate(_local, rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
	// _local = glm::rotate(_local, rotation.z, Vector3f(0.0f, 0.0f, 1.0f));
 //   	_local = glm::scale(_local, scale);

 //   	_world = Matrix4f(1.0);
 //    _world = glm::translate(_world, position);
	// _transform = _world * _local;
}

std::string		Transform::toString(void) const
{
	std::stringstream ss;
	// ss 	<< "# Component Transform #" << std::endl;
	// ss	<< "Position(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
	// ss	<< "Rotation (" << rotation.x << "," << rotation.y << "," << rotation.z << ")" << std::endl;
	// ss	<< "Scale (" << scale.x << "," << scale.y << "," << scale.z << ")" << std::endl;
	return ss.str();
}

void			Transform::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
		TABS = "\t\t\t";
	file << TABS << "TRANSFORM:" 
	<< position.x 	<< SEPARATOR_F << position.y 	<< SEPARATOR_F << position.z << SEPARATOR
	<< rotation.x 	<< SEPARATOR_F << rotation.y 	<< SEPARATOR_F << rotation.z << SEPARATOR
	<< scale.x 		<< SEPARATOR_F << scale.y 		<< SEPARATOR_F << scale.z << std::endl;
}

// PRIVATE //


// GETTER SETTER //

Matrix4f		Transform::GetMatrice() 
{ 
	CalculateTransform();
	return _transform; 
}