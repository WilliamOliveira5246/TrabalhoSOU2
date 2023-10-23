#include "trem.h"
#include <QtCore>
#include <pthread.h>

pthread_mutex_t mutexT1T2;
pthread_mutex_t mutexT1T3;
pthread_mutex_t mutexT1T4;
pthread_mutex_t mutexT2T4;
pthread_mutex_t mutexT2T5;
pthread_mutex_t mutexT3T4;
pthread_mutex_t mutexT4T5;



//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
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
                    if (y == 30 && x <470){
                        if (x == 450){
                            pthread_mutex_lock(&mutexT1T2);
                            x+=10;
                        } else{
                            x+=10;
                        }
                    }
                    else if (x == 470 && y < 150){
                        if(y == 130){
                            pthread_mutex_lock(&mutexT1T3);
                            pthread_mutex_lock(&mutexT1T4);
                        }
                        y+=10;
                    }
                    else if (x > 200 && y == 150){ //x = 330 | y = 150
                        if(x == 450){
                            pthread_mutex_unlock(&mutexT1T2);
                        } else if (x == 320){
                            pthread_mutex_unlock(&mutexT1T4);
                        }
                        x-=10;
                    }
                    else{
                        if (x == 200 && y == 130){
                            pthread_mutex_unlock(&mutexT1T3);
                        }
                        y-=10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;
        case 2: //Trem 2
                    while(velocidade == 200){
                        //parado
                    }
                    if (x == 740 && y < 150){
                        if (y == 130){
                            pthread_mutex_lock(&mutexT2T4);
                            pthread_mutex_lock(&mutexT2T5);

                        }
                        y += 10;
                    }
                    else if (x > 470 && y == 150){
                        if (x == 590){
                            pthread_mutex_unlock(&mutexT2T5);
                        } else if (x == 490){
                            pthread_mutex_lock(&mutexT1T2);
                        }
                        x -= 10;
                    }
                    else if (x == 470 && y > 30){
                        if (y == 130){
                            pthread_mutex_unlock(&mutexT2T4);
                        }
                        y -= 10;
                    }
                    else {
                        if (x == 490 && y == 30){
                            pthread_mutex_unlock(&mutexT1T2);
                        }
                        x += 10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;
        case 3:     //Trem 3
            while(velocidade == 200){
                //parado
            }
            if (y == 150 && x <340){
                if (x == 180){
                    pthread_mutex_lock(&mutexT3T4);
                    pthread_mutex_lock(&mutexT1T3);
                    x+=10;
                }else{
                    x+=10;
                }
            }
            else if (x == 340 && y < 270){
                if (y == 170){
                    pthread_mutex_unlock(&mutexT1T3);
                    y+=10;
                } else {
                    y+=10;
                }
            }
            else if (x > 70 && y == 270){
                if (x == 320){
                    pthread_mutex_unlock(&mutexT3T4);
                    x-=10;
                } else {
                    x-=10;
                }
            }
            else{
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4:     //Trem 4
            while(velocidade == 200){
                //parado
            }
            if (y == 150 && x <610){
                if (x == 360){
                    pthread_mutex_unlock(&mutexT3T4);
                    x+=10;
                } else if (x == 490){
                    pthread_mutex_unlock(&mutexT1T4);
                    x+=10;
                } else if (x == 590){
                    pthread_mutex_lock(&mutexT4T5);
                    x+=10;
                }
                else {
                    x+=10;
                }
            }
            else if (x == 610 && y < 270){
                if (y == 170){
                    y+=10;
                    pthread_mutex_unlock(&mutexT2T4);
                } else {
                    y+=10;
                }

            }
            else if (x > 340 && y == 270){
                if (x == 360){
                    pthread_mutex_lock(&mutexT3T4);
                    x-=10;
                } else if (x == 590){
                    pthread_mutex_unlock(&mutexT4T5);
                    x-=10;
                }else {
                    x-=10;
                }
            }
            else{
                if (y == 170){
                    pthread_mutex_lock(&mutexT2T4);
                    pthread_mutex_lock(&mutexT1T4);
                    y-=10;
                } else {
                    y-=10;
                }

            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5:     //Trem 5
            while(velocidade == 200){
                //parado
            }
            if (y == 150 && x < 880){
                if(x == 630){
                    pthread_mutex_unlock(&mutexT4T5);
                    x+=10;
                }
                else if (x == 760){
                     pthread_mutex_unlock(&mutexT2T5);
                     x+=10;
                }
                else {
                    x+=10;
                }
            }
            else if (x == 880 && y < 270){
                y+=10;
            }
            else if (x > 610 && y == 270){
                if (x == 630){
                    pthread_mutex_lock(&mutexT4T5);
                    x-=10;
                } else {
                    x-=10;
                }

            }
            else{
                if (y == 170){
                    pthread_mutex_lock(&mutexT2T5);
                    y-=10;
                } else {
                    y-=10;
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
