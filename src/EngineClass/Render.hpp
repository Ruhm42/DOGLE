#ifndef RENDER_HPP
# define RENDER_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Render : public IState
	{
		public:

			Render(void);
			~Render(void);
					
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

			
			// tmp
			GLuint VBO;


		private:
			
			Render &operator=(Render const &rhs);
			Render(Render const &src);

			void			_renderSkin(Skin& skin);
	};

	std::ostream	&operator<<(std::ostream &o, Render const &rhs);

#endif
