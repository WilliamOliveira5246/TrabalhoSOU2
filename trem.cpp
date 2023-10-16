#include "trem.h"
#include <QtCore>
#include <pthread.h>

pthread_mutex_t mutex;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 200;
}

bool loop2 = false;

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            while(velocidade == 200){
                //parado
            }
            if (y == 30 && x <330){
                if (x == 310){
                    pthread_mutex_lock(&mutex);
                    x+=10;
                } else{
                    x+=10;
                }
            }
            else if (x == 330 && y < 150){
                y+=10;
            }
            else if (x > 60 && y == 150){ //x = 330 | y = 150
                if(x == 320){
                    x-=10;
                    pthread_mutex_unlock(&mutex);
                } else {
                    x-=10;
                }
            }
            else{
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            while(velocidade == 200){
                //parado
            }
            if (y == 30 && x <600){
                if (x == 330 && !loop2){
                    pthread_mutex_lock(&mutex);
                    x+=10;
                } else if (x == 340) {
                    x+=10;
                    pthread_mutex_unlock(&mutex);
                } else {
                    x+=10;
                }
            }
            else if (x == 600 && y < 150)
                y+=10;
            else if (x > 330 && y == 150){ //x == 600 | y == 150
                if (x == 350){
                    pthread_mutex_lock(&mutex);
                    x-=10;
                } else {
                    x-=10;
                }
            }
            else {
                y-=10;
                if (y == 30){
                    loop2 = true;
                }
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}

void Trem::alteraVelocidade(int resultado){
    velocidade = resultado;
}



