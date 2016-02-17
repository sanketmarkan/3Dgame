

float eyex,eyey,eyea=-33,eye2a=29;
int bodyx=10,bodyy,bodyz=10;
int stx,sty,view,stc=1,kill,jump,vely,inmotion;
float cutoff=0;
float rectangle_rotation = 0,cx,cy,cz;
float vx,vy,vz,off;
double kill_time,jump_time;
float zoom=1,viewx,viewy;

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*	int i=arr[bodyy][bodyx][bodyz];
		float x = 2.5+platform[i].x;
		float z = platform[i].z+2;
		float angle = atan2(cx-x,cz-z);
		if(angle >= 45 && angle <135) angle=90;
		else if((angle >= 135 && angle <= 180) || (angle<=-135)) angle=180;
		else if((angle >= 0 && angle <= 45) || (angle<=0 && angle>=-45)) angle=0;
		else angle = 270;
		cout<<angle<<endl;
	 */
	int counter=0;
	double current_time = glfwGetTime(); 

	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_H:
				viewy++;
				break;
			case GLFW_KEY_B:
				viewx--;
				break;
			case GLFW_KEY_N:
				viewy--;
				break;
			case GLFW_KEY_M:
				viewx++;
				break;
			case GLFW_KEY_Z:
				zoom+=0.3;
				break;
			case GLFW_KEY_X:
				zoom-=0.3;
				zoom = max(0.5f,zoom);
				break;
			case GLFW_KEY_DOWN:
				if(view==4 || view==5){
					break;
				}
				rectangle_rotation = 0;
				if(arrr[bodyy][bodyx][bodyz+1]==3) break;
				//rectangle_rotation = (angle + 180);
				//if(rectangle_rotation>=360) rectangle_rotation-=360;
				bodyz++;
				current_time = glfwGetTime(); 
				inmotion = 0; 
				if(motion[bodyy][bodyx][bodyz]){
					if(hight[bodyy][bodyx][bodyz]>5&& !jump)
						bodyz=25;
					else{
						inmotion = 1;
					}
				}
				if(bodyz>=20){
					kill=1;
					red_count = 0;
			memset(redc,0,sizeof(redc));
					

					kill_time = current_time;
					bodyx=10;
					bodyz=10;
					view=0;
					cutoff=0;
				}
				break;
			case GLFW_KEY_UP:
				if(view==4 || view==5){
					int a=sin(rectangle_rotation*M_PI/180.0);
					int b=cos(rectangle_rotation*M_PI/180.0);
					if(arrr[bodyy][bodyx-a][bodyz-b]==3) break;
					bodyx-=a;
					bodyz-=b;
					if(bodyz<0 || bodyx<0 || bodyz>=20 || bodyx>=20){
					kill=1;
			memset(redc,0,sizeof(redc));
					red_count = 0;
					kill_time = current_time;
					bodyx=10;
					bodyz=10;
					view=0;
					cutoff=0;
					}
					break;
				}
				rectangle_rotation=180;
				if(arrr[bodyy][bodyx][bodyz-1]==3) break;
				bodyz--;
				//	bodyx += sin(rectangle_rotation*M_PI/180.0);
				//	bodyz += cos(rectangle_rotation*M_PI/180.0);
				//	cout<<rectangle_rotation<<endl;
				//	cout<<cos(rectangle_rotation*M_PI/180.0)<<" "<<sin(rectangle_rotation*M_PI/180.0)<<endl;
				current_time = glfwGetTime();
				inmotion = 0; 
				if(motion[bodyy][bodyx][bodyz]){
					if(hight[bodyy][bodyx][bodyz]>5&& !jump)
						bodyz=-5;
					else{
						inmotion = 1;
					}
				}
				if(bodyz<0){
					kill=1;
					red_count = 0;
			memset(redc,0,sizeof(redc));

					kill_time = current_time;
					bodyx=10;
					bodyz=10;
					view=0;
					cutoff=0;
				}
				break;
			case GLFW_KEY_LEFT:
				if(view==4 || view==5){
					rectangle_rotation += 90;
					if(rectangle_rotation >= 360) rectangle_rotation -= 360;
					break;
				}
				rectangle_rotation = 90;
				//if(rectangle_rotation>=360) rectangle_rotation-=360;
				if(arrr[bodyy][bodyx-1][bodyz]==3) break;
				bodyx--;
				inmotion = 0; 
				if(motion[bodyy][bodyx][bodyz]){
					if(hight[bodyy][bodyx][bodyz]>5&& !jump)
						bodyx=-5;
					else{
						inmotion = 1;
					}
				}
				current_time = glfwGetTime(); 
				if(bodyx<0){
					kill=1;
			memset(redc,0,sizeof(redc));
					red_count = 0;

					kill_time = current_time;
					bodyx=10;
					bodyz=10;
					view=0;
					cutoff=0;
				}
				break;
			case GLFW_KEY_RIGHT:
				if(view==4 || view==5){
					rectangle_rotation += 270;
					if(rectangle_rotation >= 360) rectangle_rotation -= 360;
					break;
				}
				rectangle_rotation = 270;
				//rectangle_rotation = (angle+90);
				//if(rectangle_rotation>=360) rectangle_rotation-=360;
				if(arrr[bodyy][bodyx+1][bodyz]==3) break;
				bodyx++;
				inmotion = 0; 
				if(motion[bodyy][bodyx][bodyz]){
					if(hight[bodyy][bodyx][bodyz]>5 && !jump)
						bodyx=25;
					else{
						inmotion = 1;
					}
				}
				if(bodyx>=20){
					kill=1;
			memset(redc,0,sizeof(redc));
					red_count = 0;

					kill_time = current_time;
					bodyx=10;
					bodyz=10;
					view=0;
					cutoff=0;
				}
				break;
			case GLFW_KEY_SPACE:
				if(!jump && !inside[bodyy][bodyx][bodyz]){
					jump=1;
					vely = 3;
					jump_time = current_time;
				}
				break;
			case GLFW_KEY_P:
				counter++;
			case GLFW_KEY_O:
				counter++;
			case GLFW_KEY_I:
				counter++;
			case GLFW_KEY_U:
				counter++;
			case GLFW_KEY_Y:
				counter++;
			case GLFW_KEY_T:
				counter++;
				view=6-counter;
				stc=1;
				break;
			case GLFW_KEY_S:
				sty=0;
				break;
			case GLFW_KEY_A:
				stx=0;
				break;
			case GLFW_KEY_W:
				sty=0;
				break;
			case GLFW_KEY_D:
				stx=0;
				break;
			default:
				break;
		}
	}
	else if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				quit(window);
				break;
			case GLFW_KEY_S:
				sty=1;
				break;
			case GLFW_KEY_A:
				stx=1;
				break;
			case GLFW_KEY_W:
				sty=2;
				break;
			case GLFW_KEY_D:
				stx=2;
				break;
			default:
				break;
		}
	}
}

void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
			quit(window);
			break;
		default:
			break;
	}
}

void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_RELEASE)
				//	triangle_rot_dir *= -1;
				break;
			//		case GLFW_MOUSE_BUTTON_RIGHT:
			//			if (action == GLFW_RELEASE) {
			//				rectangle_rot_dir *= -1;
			//			}
			//			break;
		default:
			break;
	}
}
