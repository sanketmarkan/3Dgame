#include "important.cpp"
VAO *rectangle,*circle;
VAO *head,*body,*heado;
VAO *leg,*lego,*bodyo;
VAO* cube;


std::vector<plat> platform;
float radius=2;

int arr[3][25][25],isthere[3][25][25];
int arrr[3][25][25],inside[3][25][25];
int motion[3][25][25],hight[3][25][25],dir[3][25][25];
int red_count,redc[3][5];
pair<int,int> red[3][25];


void createCircle(){
	GLfloat vertex_buffer_data [9048];
	int j=0;
	for(int i=0;i<1000;i++){
		vertex_buffer_data[j++]=radius*cos(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=radius*sin(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=radius*cos(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=radius*sin(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
	}
	vertex_buffer_data[j++] = -2;
	vertex_buffer_data[j++] = -3;
	vertex_buffer_data[j++] =  0;
	vertex_buffer_data[j++] =  2;
	vertex_buffer_data[j++] = -7;
	vertex_buffer_data[j++] = 0;
	vertex_buffer_data[j++] = 2;
	vertex_buffer_data[j++] = -7;
	vertex_buffer_data[j++] = 0;

	vertex_buffer_data[j++] = 2;
	vertex_buffer_data[j++] = -3;
	vertex_buffer_data[j++] =  0;
	vertex_buffer_data[j++] =  -2;
	vertex_buffer_data[j++] = -7;
	vertex_buffer_data[j++] = 0;
	vertex_buffer_data[j++] = 2;
	vertex_buffer_data[j++] = -3;
	vertex_buffer_data[j++] = 0;

	GLfloat color_buffer_data [9048];
	for(int i=0;i<9018;i+=3){
		color_buffer_data[i]=1;
		color_buffer_data[i+1]=0.2;
		color_buffer_data[i+2]=0.2;
	}
	circle = create3DObject(GL_TRIANGLES, 3006, vertex_buffer_data, color_buffer_data, GL_LINE);
}

VAO* createCube(float x,float y,float z,float len,float bre,float hei,float red,float green,float blue){
	GLfloat vertex_buffer_data [] = {
		x,y,z,
		x+len,y,z,
		x+len,y+bre,z,
		x,y,z,
		x+len,y+bre,z,
		x,y+bre,z,

		x,y,z+hei,
		x+len,y,z+hei,
		x+len,y+bre,z+hei,
		x,y,z+hei,
		x+len,y+bre,z+hei,
		x,y+bre,z+hei,

		x,y,z,
		x+len,y,z,
		x+len,y,z+hei,
		x,y,z,
		x,y,z+hei,
		x+len,y,z+hei,

		x+len,y,z,
		x+len,y+bre,z,
		x+len,y,z+hei,
		x+len,y+bre,z,
		x+len,y,z+hei,
		x+len,y+bre,z+hei,

		x,y,z,
		x,y+bre,z,
		x,y,z+hei,
		x,y+bre,z,
		x,y,z+hei,
		x,y+bre,z+hei,

		x,y+bre,z,
		x+len,y+bre,z,
		x+len,y+bre,z+hei,
		x,y+bre,z,
		x,y+bre,z+hei,
		x+len,y+bre,z+hei,
	};
	GLfloat color_buffer_data [905];


	for(int j=0;j<108;){
		color_buffer_data[j++]=red;
		color_buffer_data[j++]=green;
		color_buffer_data[j++]=blue;
	}
	return create3DObject(GL_TRIANGLES,36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void chances(){
	cube = createCube(0,0,0,2,2,2,1,0.2,0.2);
}

VAO* createOCube(float x,float y,float z,float len,float bre,float hei){
	x-=0.05;len+=0.1;bre+=0.1;
	y-=0.05;z-=0.05;hei+=0.1;
	GLfloat vertex_buffer_data [] = {
		x,y,z,
		x+len,y,z,
		x+len,y,z,
		x+len,y+bre,z,
		x+len,y+bre,z,
		x,y+bre,z,
		x,y+bre,z,
		x,y,z,

		x,y,z+hei,
		x+len,y,z+hei,
		x+len,y,z+hei,
		x+len,y+bre,z+hei,
		x+len,y+bre,z+hei,
		x,y+bre,z+hei,
		x,y+bre,z+hei,
		x,y,z+hei,

		x,y,z,
		x,y,z+hei,
		x+len,y,z,
		x+len,y,z+hei,
		x+len,y+bre,z,
		x+len,y+bre,z+hei,
		x,y+bre,z,
		x,y+bre,z+hei,
	};
	GLfloat color_buffer_data [905];
	for(int j=0;j<72;j++)
		color_buffer_data[j]=0;
	return create3DObject(GL_LINES,24, vertex_buffer_data, color_buffer_data, GL_LINE);
}


void createPerson(){
	head=createCube(-2,7,0,5,3,3,1,0,0);
	heado=createOCube(-2,7,0,5,3,3);
	body=createCube(-0.75,3,0.25,2.5,3.5,2.5,1,0,0);
	bodyo=createOCube(-0.75,3,0.25,2.5,3.5,2.5);
	leg=createCube(0,0,0.25,1,3.75,2.5,1,0,0);
	lego=createOCube(0,0,0.25,1,3.75,2.5);
}

VAO* createLCube(float x,float y,float z,float len,float bre,float hei,int q){
	GLfloat vertex_buffer_data [] = { 
		x,y,z,
		x+len,y,z,
		x+len,y,z+hei,
		x,y,z,
		x,y,z+hei,
		x+len,y,z+hei,

		x,y,z,
		x+len,y,z,
		x+len,y+bre,z,
		x,y,z,
		x+len,y+bre,z,
		x,y+bre,z,

		x,y,z+hei,
		x+len,y,z+hei,
		x+len,y+bre,z+hei,
		x,y,z+hei,
		x+len,y+bre,z+hei,
		x,y+bre,z+hei,

		x+len,y,z,
		x+len,y+bre,z,
		x+len,y,z+hei,
		x+len,y+bre,z,
		x+len,y,z+hei,
		x+len,y+bre,z+hei,

		x,y,z,
		x,y+bre,z,
		x,y,z+hei,
		x,y+bre,z,
		x,y,z+hei,
		x,y+bre,z+hei,

		x,y+bre,z,
		x+len,y+bre,z,
		x+len,y+bre,z+hei,
		x,y+bre,z,
		x,y+bre,z+hei,
		x+len,y+bre,z+hei,
	};
	/*
	   int k=108;
	   for (int i = 0; i < 1; i++){
	   vertex_buffer_data[k++]=x-0.5;
	   vertex_buffer_data[k++]=y+bre;
	   vertex_buffer_data[k++]=z+hei;
	   vertex_buffer_data[k++]=x+2-0.5;
	   vertex_buffer_data[k++]=y+bre;
	   vertex_buffer_data[k++]=z+hei;
	   vertex_buffer_data[k++]=x-0.5;
	   vertex_buffer_data[k++]=y+bre-1;
	   vertex_buffer_data[k++]=z+hei;

	   vertex_buffer_data[k++]=x+2-0.5;
	   vertex_buffer_data[k++]=y+bre-1;
	   vertex_buffer_data[k++]=z+hei;
	   vertex_buffer_data[k++]=x+2-0.5;
	   vertex_buffer_data[k++]=y+bre;
	   vertex_buffer_data[k++]=z+hei;
	   vertex_buffer_data[k++]=x+1-0.5;
	   vertex_buffer_data[k++]=y+bre-1;
	   vertex_buffer_data[k++]=z+hei;		
	   }*/
	GLfloat color_buffer_data [905];
	int j=0;
	while(j<18){
		color_buffer_data[j++]=0.503;
		color_buffer_data[j++]=0.221;
		color_buffer_data[j++]=0;
	}
	while(j<90){
		color_buffer_data[j++]=0.703;
		color_buffer_data[j++]=0.421;
		color_buffer_data[j++]=0.147;
	}
	if(q==2) while(j<108){
		color_buffer_data[j++]=1;
		color_buffer_data[j++]=0.2;
		color_buffer_data[j++]=0.2;
	}
	else
	while(j<108){
		color_buffer_data[j++]=q?1:0.003;
		color_buffer_data[j++]=q?0.411:0.557;
		color_buffer_data[j++]=q?0.705:0.067;
	}
	//while(j<126)
	//	color_buffer_data[j++]=0;
	return create3DObject(GL_TRIANGLES,36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void createPlatform(){
	int a,b;
		for(int r=0;r<3;r++){
		a=0;
		int arrq[4];
		pair<int,int> qq[4];
		for(int i=0;i<=r;i++)
			arrq[i]= rand()%6;
		for(int i=0;i<=r;i++){
			if(arrq[i]==0) qq[i]=make_pair(1,1);
			if(arrq[i]==1) qq[i]=make_pair(18,3);
			if(arrq[i]==2) qq[i]=make_pair(1,8);
			if(arrq[i]==3) qq[i]=make_pair(1,18);
			if(arrq[i]==4) qq[i]=make_pair(15,18);
			if(arrq[i]==5) qq[i]=make_pair(17,13);
		}
		for (int i=0;i<20;i++){
			b=0;
			for(int j=0;j<20;j++){
				int q=0;

				for(int var=0;var<=r;var++)
					if(i==qq[var].first && j==qq[var].second ){
						q=2;
						red[r][var] =  qq[var];
					}
				plat x;
				if(i==10 && j==10)
					q=1;
				int y=arrr[r][i][j]+1;
				for(int t=0;t<y;t++){
					x.vao.push_back(createLCube(-50+a,5*t-5,-25+b,5,5,5,q));
					x.border.push_back(createOCube(-50+a,5*t-5,-25+b,5,5,5));
				}
				if(inside[r][i][j]){
					x.vao.push_back(createCube(-50+a,15,-25+b,5,0.2,5,0.003,0.557,0.067));
					//x.border.push_back(createOCube(-25+a,5*y-5,-25+b,5,5,5));
				}
				x.x=-50+a; 
				x.x+=r%2?50:-50;
				x.y=-50*(r-1)+5*y-5;
				x.z=-25+b-13;
				arr[r][i][j]=platform.size();
				platform.push_back(x);
				b+=5.8;
			}
			a+=5.8;
		}
	}
}


// Creates the rectangle object used in this sample code
void createRectangle ()
{
	// GL3 accepts only Triangles. Quads are not supported
	static const GLfloat vertex_buffer_data [] = {
		0,0,0, // vertex 1
		5,0,0, // vertex 2
		5,10,0, // vertex 3

		5,10,0, // vertex 3
		0,0,0, // vertex 4
		0,10,0  // vertex 1
	};

	static const GLfloat color_buffer_data [] = {
		1,0,0, // color 1
		0,0,1, // color 2
		0,1,0, // color 3

		0,1,0, // color 3
		0.3,0.3,0.3, // color 4
		1,0,0  // color 1
	};

	// create3DObject creates and returns a handle to a VAO that can be used later
	rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}
