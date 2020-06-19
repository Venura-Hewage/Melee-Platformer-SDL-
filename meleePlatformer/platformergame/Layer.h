#ifndef _Layer_
#define _Layer_

class Level;

class Layer
{
public:
	Layer();
	virtual void render() =0;
	virtual void update(Level* pLevel) =0;


protected:

	virtual ~Layer() {}



};


#endif