#include "initobjects.cpp"
#include "initgame.cpp"

float camera_rotation_angle = 45;


void draw (){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram (programID);
	if(kill){
		glm::vec3 eye (0, 10, 10);
		glm::vec3 target (0, 0, 0);
		glm::vec3 up (0, 1, 0);
		Matrices.projection = glm::ortho(-20.0f,20.0f,-20.0f,20.0f, 0.1f, 200.0f);
		Matrices.view = glm::lookAt(eye,target,up);
		glm::mat4 VP = Matrices.projection * Matrices.view;
		glm::mat4 MVP;	
		Matrices.model = glm::mat4(1.0f);
		MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(circle);
	}
	else{
		int i=arr[bodyy][bodyx][bodyz];
		//	translate = glm::translate (glm::vec3(2.5+platform[i].x,platform[i].y, platform[i].z+2));

		glm::vec3 eye (cx,cy,cz);
		//glm::vec3 eye (0,0,0);
		glm::vec3 target (0, 0, 0);
		glm::vec3 up (0, 1, 0);
		if(view==1)
			up=glm::vec3(0,0,-1);
		if(view==4){
			//Matrices.projection = glm::frustum(-49.0f, 49.0f, -49.0f, 49.0f, 49.0f, 200.0f);
			Matrices.projection = glm::perspective(45.0f, (1366.0f/766.0f), 15.5f, 200.0f);
			target = glm::vec3(2.5+platform[i].x,platform[i].y+vely+off+9, platform[i].z+2);
			//up=glm::vec3(0,0,-1);
		}
		else if(view==5){
			//Matrices.projection = glm::frustum(-49.0f, 49.0f, -49.0f, 49.0f, 49.0f, 200.0f);
			Matrices.projection = glm::perspective(45.0f, (1366.0f/766.0f), 15.5f, 200.0f);
			target = glm::vec3(2.5+platform[i].x,platform[i].y+vely+off+9, platform[i].z+2);
			//up=glm::vec3(0,0,-1);
		}
		else
			Matrices.projection = glm::frustum(-77.0f/zoom+viewx, 77.0f/zoom+viewx, -60.0f/zoom+viewy, 60.0f/zoom+viewy, 150.0f, 500.0f);

		//cout<<2.5+platform[i].x<<" "<<platform[i].y<<" "<< platform[i].z+2<<endl;
		Matrices.view = glm::lookAt(eye,target,up);
		glm::mat4 VP = Matrices.projection * Matrices.view;
		glm::mat4 MVP;	
		Matrices.model = glm::mat4(1.0f);

		glm::mat4 rotate;
		glm::mat4 translate;
		int start=0;
		if(view==1) start=bodyy; 
		for(int r=start;r<3;r++)
			for(int j=0;j<20 && j<cutoff;j++)
				for(int k=0;k<20 && k<cutoff;k++)
					if(isthere[r][j][k] || r!=bodyy){
						int i=arr[r][j][k];
						translate = glm::translate (glm::vec3(r%2?50:-50, -50*(r-1), -13));        // glTranslatef
						if(motion[r][j][k] && r==bodyy)
						translate = glm::translate (glm::vec3(r%2?50:-50, hight[r][j][k]-50*(r-1), -13));        // glTranslatef
						Matrices.model = translate ;
						MVP = VP * Matrices.model;
						glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
						for(int q=0;q<platform[i].vao.size() ;q++){
							draw3DObject(platform[i].vao[q]);
							if(q<platform[i].border.size())
								draw3DObject(platform[i].border[q]);
						}
					}
		for(int i=0;i<bodyy;i++){
		translate = glm::translate (glm::vec3(-50.0f,55.0f,0.0f));        // glTranslatef
		Matrices.model = translate;
		MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(cube);
		}

		cutoff+=0.25;
		if(cutoff>10){
		//cout<<rectangle_rotation<<endl;
		translate = glm::translate (glm::vec3(2.5+platform[i].x,platform[i].y+vely+off, platform[i].z+2));        // glTranslatef
		rotate = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,1,0)); 
		Matrices.model = (translate * rotate);
		MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(head);
		draw3DObject(heado);
		draw3DObject(body);
		draw3DObject(bodyo);

		glm::mat4 translate1 = glm::translate (glm::vec3(-2,0,0));        // glTranslatef
		glm::mat4 translate2 = glm::translate (glm::vec3(2,0,0));        // glTranslatef

		translate = glm::translate (glm::vec3(4.5+platform[i].x,platform[i].y+vely+off, platform[i].z+2));        // glTranslatef
		rotate = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,1,0)); 
		Matrices.model = ( translate * translate1 * rotate * translate2 );
		MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(leg);
		draw3DObject(lego);
		translate = glm::translate (glm::vec3(0.5+platform[i].x,platform[i].y+vely+off, platform[i].z+2));        // glTranslatef
		rotate = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,1,0)); 
		Matrices.model = ( translate*translate2 * rotate * translate1 );
		//	  Matrices.model = (translate * rotate);
		//Matrices.model = (rotate * translate );
		MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);	  
		draw3DObject(leg);
		draw3DObject(lego);
}
		float increments = 1;
		// rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;
	}
}


int main (int argc, char** argv)
{
	int width = 1366;
	int height = 768;
	GLFWwindow* window = initGLFW(width, height);


	int c=0;
	string line;
	ifstream myfile;
	myfile.open ("example.txt", ios::in);
	if (myfile.is_open()){
		while ( getline (myfile,line)){
			for(int i=0;i<20;i++)
				arrr[c/20][i][c%20]=line[i]-'0';
			c++;
		}
		myfile.close();
	}
	myfile.close();
	c=0;
	myfile.open ("inside.txt", ios::in);
	if (myfile.is_open()){
		while ( getline (myfile,line)){
			for(int i=0;i<20;i++)
				inside[c/20][i][c%20]=line[i]-'0';
			c++;
		}
		myfile.close();
	}

	initGL (window, width, height);

	double last_update_time = glfwGetTime(), current_time ;

	for(int k=0;k<3;k++)
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
				isthere[k][i][j]=1;

	for(int k=0;k<3;k++)
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++){
				int x=rand()%10;
				if(!x && !inside[k][i][j]) isthere[k][i][j]=0;
				isthere[k][10][10]=1;
			}

	for(int k=0;k<3;k++)
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++){
				int x=rand()%9;
				if(!x && !inside[k][i][j]){ dir[k][i][j] = (rand()%2)*2-1; motion[k][i][j]=1;}
				motion[k][10][10]=0;
				dir[k][10][10]=0;
			}


	while (!glfwWindowShouldClose(window)) {
	//	cout<<red_count<<endl;
		for(int i=0;i<=bodyy;i++){
			if(red[bodyy][i].first == bodyx && !redc[bodyy][i] && red[bodyy][i].second == bodyz){
				red_count++;
				redc[bodyy][i] = 1;
			}
		//	cout<<bodyx<<" "<<bodyz<<endl;
		//	cout<<red[bodyy][i].first<<" "<<red[bodyy][i].second<<endl;
		}
		off = hight[bodyy][bodyx][bodyz];
		current_time = glfwGetTime(); 
		if(!isthere[bodyy][bodyx][bodyz] && !jump){
			kill=1;
			red_count = 0;
			memset(redc,0,sizeof(redc));
			kill_time = current_time;
			view=0;
			bodyx=10;
			bodyz=10;
			cutoff = 0;
		}
		if(current_time-kill_time>=2)
			kill=0;
		if(view==3){
			double xpos, ypos;
			int width,height;
			glfwGetCursorPos(window,&xpos, &ypos);
			glfwGetFramebufferSize(window, &width, &height);
			xpos=-77+(float)154.0/width*xpos;
			ypos=-60+(float)120.0/height*ypos;
			ypos*=-1;
			//cout<<xpos<<" "<<ypos<<endl;
			eye2a = ypos;
			eyea=xpos;
		}
		if(view==0 || view == 3){
			cx=250*sin(eyea*M_PI/180.0);
			cy=5*eye2a;
			cz=250*cos(eyea*M_PI/180.0);
		}
		if(view==4){
			int i=arr[bodyy][bodyx][bodyz];
			float theta = (rectangle_rotation)*M_PI/180.0f ,hh = 20 ;
			cx = 2.5+platform[i].x + hh*sin(theta);
			cy = platform[i].y+vely+off+9; 
			cz = platform[i].z+2 + hh*cos(theta);
		}

		if(view==5){
			int i=arr[bodyy][bodyx][bodyz];
			float theta = (rectangle_rotation)*M_PI/180.0f ,hh = 14 ;
			cx = 2.5+platform[i].x + hh*sin(theta);
			cy = platform[i].y+vely+off+9; 
			cz = platform[i].z+2 + hh*cos(theta);
		}
		
		if(stc==1){
			if(view == 1 ){
				cx=0;
				cz=0;
				cy=250;
			}
			if(view == 2){
				cx=5*-13.7819;
				cy=250;
				cz=5*48.0631;
			}
			stc=0;
		}
		draw();
		/*
		    else if(stc==2){
		    int c=0;
		//cx=vx;cy=vy;cz=vz;
		cout<<cx<<" "<<vx<<" "<<cy<<" "<<vy<<" "<<cz<<" "<<vz<<endl;
		if(cx==vx) c++;
		else if(vx>cx)cx++;
		else if(vx<cx && cx-vx<1){cx=vx;c++;} 
		else cx--;
		if(cy==vy)c++;
		else if(vy>cy)cy++;
		else if(vy<cy &&cy-vy<1){cy=vy;c++;} 
		else cy--;
		if(cz==vz)c++;
		else if(vz>cz)cz++;
		else if(vz<cz && cz-vz<1){cz=vz;c++;} 
		else cz--;
		if(c==3) stc=0;
		}*/
		//cout<<view<<endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
		if(current_time-jump_time>0.1){
			if(jump){
			if(jump==1) vely+=3;
			if(vely>15 || jump==2){
				vely-=3;
				jump=2;
			}
			if(vely==0)
				jump=0;
  			}
  			jump_time=current_time;
		}
		if ((current_time - last_update_time) >= 0.08) { 
			if(bodyx==10 && bodyz==10 && red_count >= bodyy+1){
			  bodyx=bodyz=10;
			  bodyy=(bodyy+1)%3;
			  red_count=0;
			  }
			  for(int k=0;k<3;k++)
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++){
				hight[k][i][j]+=dir[k][i][j];
				if(abs(hight[k][i][j])>16)
					dir[k][i][j]*=-1;
			}
			if(stx==1) eyea--;
			else if(stx) eyea++;
			if(sty==1) eye2a=max(-25.0f,eye2a-1); 
			else if(sty) eye2a=min(35.0f,eye2a+1);
			last_update_time = current_time;
		}
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
