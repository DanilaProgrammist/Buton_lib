#include "main.h"
#include "button.h"
Button btn;
int main(void){
	ButtInit(&btn, Button_Pin, Button_GPIO_Port, CLICK);
	while(1){
		if(ButtTrigg(&btn) == 1){
			//do something
		}
	}
	return 1;
}
