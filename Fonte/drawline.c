//BufferPool
#include "buffend.h"

int drawline(tp_buffer *buffpoll, tp_table *s, struct fs_objects objeto, int p, int num_page) {
     
    if (num_page > PAGES || p > SIZE) {
        return ERRO_DE_PARAMETRO;
    }
    int *pos_ini, aux = (p * tamTupla(s,objeto)) , num_reg = objeto.qtdCampos;
    pos_ini = &aux;
    int count, pos_aux, bit_pos;
    union c_double cd;
    union c_int ci;
    int x = 0;
    
    count = pos_aux = bit_pos = 0;
    
    for(count = 0; count < num_reg; count++) {
        pos_aux = *(pos_ini);
        bit_pos = 0;

        switch(s[count].tipo) {
            case 'S':
                x = 0;
                while(buffpoll[num_page].data[pos_aux] != '\0'){
            
                    printf("%c", buffpoll[num_page].data[pos_aux]);
                    if ((buffpoll[num_page].data[pos_aux++] & 0xc0) != 0x80) bit_pos++; //Conta apenas bits que possam ser impressos (UTF8)
                x++;
                }
                
                cria_campo((TAMANHO_NOME_CAMPO - (bit_pos)), 0, (char*)' ', (30 - x));
                break;
            
            case 'I':
                while(pos_aux < *(pos_ini) + s[count].tam){
                    ci.cnum[bit_pos++] = buffpoll[num_page].data[pos_aux++];
                }
                printf("%d", ci.num); //Controla o número de casas até a centena
                cria_campo((TAMANHO_NOME_CAMPO - (bit_pos)), 0, (char*)' ', 28);
                break;
                
            case 'D':
                while(pos_aux < *(pos_ini) + s[count].tam){
                    cd.double_cnum[bit_pos++] = buffpoll[num_page].data[pos_aux++]; // Cópias os bytes do double para área de memória da union
                }
                printf("%.3lf", cd.dnum);
                cria_campo((TAMANHO_NOME_CAMPO - (bit_pos)), 0, (char*)' ', 24);
                break;
            
            case 'C': 
                printf("%c", buffpoll[num_page].data[pos_aux]);
                if(s[count].tam < strlen(s[count].nome)){
                    bit_pos = strlen(s[count].nome);
                }
                else{
                    bit_pos = s[count].tam;
                }
                cria_campo((bit_pos - 1), 0, (char*)' ', 29);   
                break;
            
            default: 
                return ERRO_IMPRESSAO;
                break;
        }
        *(pos_ini) += s[count].tam;     
    }
    printf("\n");
    return SUCCESS;
}