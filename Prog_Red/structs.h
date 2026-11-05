typedef struct{
    int res;
    int num1;
    int num2;
    char operacion;
} Calculo;

typedef struct{
    int id_player;
    char nombre[50];
    int edad;
    int vida;
} Usuario;

typedef struct{
    long long t_cli_envio_ms;
} Latencia;

typedef struct{
    int tipo;
    union{
        Calculo Calculo;
        Usuario Usuario;
        Latencia Latencia;
    };
} PKT;