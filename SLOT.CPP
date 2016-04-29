#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<dos.h>

const int w=15;
const int MAR=10;

class shape
{
	protected:
		int xCo,yCo;
		int linecolor;
		int fillcolor;
	public:
		shape()
		{
			xCo=0;
			yCo=0;
			linecolor=WHITE;
			fillcolor=WHITE;
		}
		void set(int x,int y,int lc,int fc)
		{
			xCo=x;
			yCo=y;
			linecolor=lc;
			fillcolor=fc;
		}
		void draw()
		{
			setcolor(linecolor);
			setfillstyle(SOLID_FILL,fillcolor);
		}
};

class ball: public shape
{
	public:
		ball():shape()
		{}
		void set(int x,int y,int lc, int fc)
		{
			shape::set(x,y,lc,fc);
		}
		void draw()
		{
			shape::draw();
			circle(xCo,yCo,w);
			floodfill(xCo,yCo,linecolor);
		}
};

class rect: public shape
{
	public:
		rect():shape()
		{}
		void set(int x,int y,int lc, int fc)
		{
			shape::set(x,y,lc,fc);
		}
		void draw()
		{
			shape::draw();
			rectangle(xCo-w,yCo-w,xCo+w,yCo+w);
			floodfill(xCo,yCo,linecolor);
			moveto(xCo-w,yCo-w);
			lineto(xCo+w,yCo+w);
		}
};

class tria: public shape
{
	public:
		tria():shape()
		{}
		void set(int x,int y,int lc, int fc)
		{
			shape::set(x,y,lc,fc);
		}
		void draw()
		{
			int triarray[]={xCo,yCo-w,xCo+w,yCo+w,xCo-w,yCo+w};
			shape::draw();
			fillpoly(3,triarray);
		}
};

class noshape: public shape
{
	public:
		void erase()
		{
			int border[]={	xCo-w-MAR,yCo-w-MAR,
					xCo+w+MAR,yCo-w-MAR,
					xCo+w+MAR,yCo+w+MAR,
					xCo-w-MAR,yCo+w+MAR
					};
			setfillstyle(SOLID_FILL,DARKGRAY);
			fillpoly(4,border);
		}
};

class Cherry: public ball, public noshape
{
	public:
		Cherry():ball()
		{}
		void set(int x,int y)
		{
			ball::set(x,y,WHITE,RED);
			noshape::set(x,y,WHITE,RED);
		}
		void draw()
		{
			erase();
			ball::draw();
		}
};

class Grape: public ball, public noshape
{
	public:
		Grape():ball()
		{}
		void set(int x,int y)
		{
			ball::set(x,y,WHITE,BLUE);
			noshape::set(x,y,WHITE,BLUE);
		}
		void draw()
		{
			erase();
			ball::draw();
		}
};

class Square: public rect, public noshape
{
	public:
		Square():rect()
		{}
		void set(int x,int y)
		{
			rect::set(x,y,WHITE,CYAN);
			noshape::set(x,y,WHITE,CYAN);
		}
		void draw()
		{
			erase();
			rect::draw();
		}
};

class Pyramid: public tria, public noshape
{
	public:
		Pyramid():tria()
		{}
		void set(int x,int y)
		{
			tria::set(x,y,WHITE,GREEN);
			noshape::set(x,y,WHITE,GREEN);
		}
		void draw()
		{
			erase();
			tria::draw();
		}
};

class Wheel: public shape
{
	private:
		Cherry ch;
		Grape gr;
		Square sq;
		Pyramid py;
	public:
		wheel()
		{
			xCo=0;
			yCo=0;
		}
		void set(int x,int y)
		{
			xCo=x;
			yCo=y;
			ch.set(xCo,yCo);
			gr.set(xCo,yCo);
			sq.set(xCo,yCo);
			py.set(xCo,yCo);
		}
		void draw()
		{
			setcolor(WHITE);
			rectangle(xCo-w-MAR,yCo-w-MAR, xCo+w+MAR,yCo+w+MAR);
			switch(random(4))
			{
				case 0: ch.draw();break;
				case 1: gr.draw();break;
				case 2: sq.draw();break;
				case 3: py.draw();break;
			}
		}

};

void main()
{
	const int NUMBER=60;
	int driver,mode;
	driver=DETECT;
	initgraph(&driver, &mode,"C:\\TurboC3\\BGI");
	randomize();

	Wheel w1,w2,w3;

	w1.set(100,100);
	w2.set(160,100);
	w3.set(220,100);

	for(int j=0; j<NUMBER; j++)
	{
		w1.draw();
		w2.draw();
		w3.draw();
		sound(100);
		delay(20);
		nosound();
		delay(j*j/20);
	}

	sound(400);
	delay(400);
	sound(500);
	delay(800);
	nosound();
	getche();
	closegraph();
}
