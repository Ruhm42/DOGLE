#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"


	class Transform : public IComponent
	{
		static size_t	counter;

		public:
			Transform();
			Transform(Vector3f pos, Vector3f rot = Vector3f(0.0f), Vector3f sc = Vector3f(1.0f));
			Transform(Transform const &src);
			~Transform(void);
		
			Transform &operator=(Transform const &rhs);
			
			Vector3f	position;
			Vector3f	rotation;
			Vector3f	scale;
			Transform	*parent;

			void		CalculateTransform();
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			Matrix4f	GetMatrice();

		private:

			Matrix4f	_transform;
			Matrix4f	_local;
			Matrix4f	_world;
	};

	std::ostream	&operator<<(std::ostream &o, Transform const &rhs);

#endif
