// --------------------------------- //
//    COMPILADORES - TRABALHO 01     //
//           ANALISE LEXICA          //
// --------------------------------- //
//   ALICE TELES LUCENA - 22050309   //
//   IGOR DE SOUZA LIMA - 22052565   //
// --------------------------------- //

///////////////////////////////////////

// INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// DEFINICAO DO TIPO DO PAR: TOKEN, LEXEMA
typedef struct token_lexema_t{
  char token[30]; // token definido com tamanho maximo (string)
  char lexema[1000]; // lexema definido com tamanho maximo (string)
} token_lexema_t;

///////////////////////////////////////
// FUNÇÕES
///////////////////////////////////////

// verifica se CHAR é pontuação
bool pontuacao(char check_char){

  // vetor com char's que representam pontuação
  char pontuacao_array[] = {',', ';', '(', ')', '[', ']', '{', '}'};

  // percorre vetor pontuacao_array
  for (int i = 0; i < 9; i++){

    // se o char for igual a um dos elementos do vetor
    if (check_char == pontuacao_array[i]){
      return true; // é pontuação
    } // end if
    
  } // end for
  
  return false; // não é pontuação
  
} // end 

// verifica se CHAR é tipo
bool tipo(char *check_type){

  // vetor com char's que representam pontuação
  char *tipo_array[] = {"VOID", "INT", "FLOAT", "CHAR"};

  // percorre vetor tipo_array
  for (int i = 0; i < 4; i++){

    // se o char for igual a um dos elementos do vetor
    if (strcmp(tipo_array[i], check_type) == 0){
      return true; // é tipo
    } // end if
    
  } // end for
  
  return false; // não é pontuação
  
} // end 

// verifica se CHAR é dígito
bool digito(char check_char){

  // vetor com char's que representam dígitos
  char digito_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  // percorre vetor digito_array
  for (int i = 0; i < 10; i++){

    // se o char for igual a um dos elementos do vetor
    if (check_char == digito_array[i]){
      return true; // é dígito
    } // end if
    
  } // end for
  
  return false; // não é dígito
  
} // end

// verifica se NUMBER é FLOAT
bool number_float(char *check_number){

  // verifica elementos iniciais
  if (digito(check_number[0]) == true || 
     (check_number[0] == '-' && digito(check_number[1]) == true) || 
     (check_number[0] == '+' && digito(check_number[1]) == true)){

    // verifica presença do ponto
    if (strstr(check_number, ".")){
      return true; // há ponto -> é float
    } // end if
    
  } // end if
  
  return false; // não é float
  
} // end

// verifica se há ERRO no FLOAT
bool error_float(char *check_float){
  
  int size_float = strlen(check_float); // tamanho do número
  int point = 0; // não há ponto no número

  // leitura de cada elemento no número
  for (int i = 0; i < size_float; i++){

    // se o primeiro elemento for '+' ou '-'
    if (i == 0 && (check_float[i] == '+' || check_float[i] == '-')){ 
      continue; // continua loop
    } // end if

    // se elemento é ponto
    else if (check_float[i] == '.'){ 

      // se ponto está na última posição
      if (i == size_float - 1){
        return true; // há erro
      } // end if
        
      // se ponto não existe no número ainda
      else if (point == 0){ 
        point = 1; // define ponto como existente
      } // end else if

      // qualquer outro caso
      else { 
        return true; // há erro
      } // end if/else
      
    } // end else if

    // se elemento não for um dígito
    else if (digito(check_float[i]) == false){
      return true; // há erro
    } // end else if
    
  } // end for

  // verifica se há ponto no número
  if (point == 0){
    return true; // não há ponto -> há erro
  } else {
    return false; // há ponto -> não há erro
  } // end if/else
  
} // end

// verifica se NUMBER é INT
bool number_int(char *check_number){

  // verifica elementos iniciais
  if (digito(check_number[0]) == true || 
     (check_number[0] == '-' && digito(check_number[1]) == true) || 
     (check_number[0] == '+' && digito(check_number[1]) == true)){

    // verifica presença do ponto
    if (strstr(check_number, ".")){
      return false; // há ponto -> não é int
    } else {
      return true; // não há ponto -> é int
    } // end if/else
    
  } // end if
  
  return false; // não é int
  
} // end 

// verifica se há ERRO no INT
bool error_int(char *check_int){
  
  int size_int = strlen(check_int); // tamanho do número

  // leitura de cada elemento no número
  for (int i = 0; i < size_int; i++){

    // se o primeiro elemento for '+' ou '-'
    if (i == 0 && (check_int[i] == '+' || check_int[i] == '-')){
      continue; // continua loop
    } // end if

    // se elemento não for um dígito
    else if (digito(check_int[i]) == false){
      return true; // há erro
    } // end else if
    
  } // end for
  
  return false; // não há erro
  
} // end

// verifica se CHAR pode ser início de ID
bool id_char(char check_char){

  // vetor com CHAR's possíveis no início de um ID
  char char_array[] = {'$', '_', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  // percorre cada elemento do vetor char_array[]
  for (int i = 0; i < 54; i++){

    // se o char for um dos elementos
    if (check_char == char_array[i]){
      return true; // válido
    } // end if
    
  } // end for
  
  return false; // inválido
  
} // end

// verifica se ID é válido
bool id(char* check_id){
  
  int id_size = strlen(check_id); // tamanho da string

  // se o primeiro char é válido para um ID
  if (id_char(check_id[0]) == true){

    // percorre cada elemento da string
    for (int i = 1; i < id_size; i++){

      // se o elemento for dígito ou char válido
      if (id_char(check_id[i]) == true || digito(check_id[i]) == true){
        continue; // continua loop
      } else {
        return false; // não é ID
      } // end if/else
      
    } // end for
    
  } else { 
    return false; // não é ID
  } // end if/else
  
  return true; // é ID
  
} // end

///////////////////////////////////////////

// retorna apenas 1 CHAR do arquivo de entrada por vez
char prox_char(FILE *f){

  char ch; // inicializacao
  fscanf(f, "%c", &ch); // leitura de 1 char
  return ch;// retorna char
  
} // end prox_char()

// denomina um token para cada lexema lido
token_lexema_t analex(char* lexema){

  token_lexema_t result; // inicializa struct (token,lexema)
  strcpy(result.lexema, lexema); // insere lexema em result

  ///////////////////////////////////////////
  // COMENTÁRIOS

  // verifica se é COMENTÁRIO
  if (lexema[0] == '/'){

    // se for COMENTÁRIO LONGO
    if (lexema[1] == '*'){
      strcpy(result.token, "COMENTÁRIO LONGO");
      return result; // retorna (token, lexema)
    } // end if

    // se for COMENTÁRIO CURTO
    if (lexema[1] == '/') {
      strcpy(result.token, "COMENTÁRIO CURTO");
      return result; // retorna (token, lexema)
    } // end if
    
  } // end if

  ///////////////////////////////////////////
  // PALAVRAS RESERVADAS E SEUS TOKENS
  
  char *reservadas_token[] = {"VOID", "INT", "FLOAT", "CHAR", "BOOL",
                              "IF", "ELSE", "FOR", "WHILE", "DO", "RETURN",
                              "BREAK", "CONTINUE", "GOTO", "TRUE", "FALSE", "MAIN", NULL};
  char *reservadas_lexema[] = {"void", "int", "float", "char", "bool",
                              "if", "else", "for", "while", "do", "return",
                              "break", "continue", "goto", "true", "false", "main", NULL};
  
  // contador auxiliar
  int i = 0;

  // para cada lexema no vetor
  while (reservadas_lexema[i]){

    // verifica se é igual ao lexema lido
    if (strcmp(lexema, reservadas_lexema[i]) == 0){
      strcpy(result.token, reservadas_token[i]);
      return result; // retorna (token, lexema)
    } // end if
    
    i++; // incrementa contador
    
  } // end while

  ///////////////////////////////////////////
  // OPERADORES E SEUS TOKENS
  
  char *op_token[] = {"OP_ARIT_ADD", "OP_ARIT_SUB", "OP_ARIT_MUL", "OP_ARIT_DIV",
                      "OP_ARIT_MOD", "OP_ARIT_INC", "OP_ARIT_DEC",
                      "OP_REL_EQL", "OP_REL_DIF", "OP_REL_GT", "OP_REL_LT", 
                      "OP_REL_GTE", "OP_REL_LTE",
                      "OP_LOG_AND", "OP_LOG_OR", "OP_LOG_NOT",
                      "OP_BIT_AND", "OP_BIT_OR", "OP_BIT_XOR", "OP_BIT_1CMP",
                      "OP_BIT_LSH", "OP_BIT_RSH",
                      "OP_ASSIGN_SIMPLE", "OP_ASSIGN_ADD", "OP_ASSIGN_SUB",
                      "OP_ASSIGN_MUL", "OP_ASSIGN_DIV", "OP_ASSIGN_MOD",
                      "OP_ASSIGN_LSH", "OP_ASSIGN_RSH", "OP_ASSIGN_ANDB",
                      "OP_ASSIGN_ORB", "OP_ASSIGN_XORB", NULL};
  char *op_lexema[] = {"+", "-", "*", "/", "%", "++", "--",
                      "==", "!=", ">", "<", ">=", "<=",
                      "&&", "||", "!", 
                      "&", "|", "^", "~","<<", ">>",
                      "=", "+=", "-=", "*=", "/=", "&=",
                      "<<=", ">>=", "&=", "|=", "^=",
                      NULL};

  // contador auxiliar
  i = 0;

  // para cada lexema no vetor
  while (op_lexema[i]){

    // verifica se é igual ao lexema lido
    if (strcmp(lexema, op_lexema[i]) == 0){
      strcpy(result.token, op_token[i]);
      return result; // retorna (token, lexema)
    } // end if
    
    i++; // incrementa contador
    
  } // end while

  ///////////////////////////////////////////
  // PONTUAÇÃO E SEUS TOKENS
  
  char *pontuacao_token[] = {"PONT_COMMA", "PONT_SEMICOLON", 
                            "PONT_PARENTHESES1", "PONT_PARENTHESES2",   
                            "PONT_BRACKETS1", "PONT_BRACKETS2",
                            "PONT_BRACES1", "PONT_BRACES2", NULL};
  char *pontuacao_lexema[] = {",", ";", "(", ")", "[", "]", "{", "}", NULL};

  //contador auxiliar
  i = 0;

  // para cada lexema no vetor
  while (pontuacao_lexema[i]){

    // verifica se é igual ao lexema lido
    if (strcmp(lexema, pontuacao_lexema[i]) == 0){
      strcpy(result.token, pontuacao_token[i]);
      return result; // retorna (token, lexema)
    } // end if

    i++; // incrementa contador
    
  } // end while

  ///////////////////////////////////////////
  // OPERADORES DIVERSOS E SEUS TOKENS
  
  char *diversos_token[] = {"OP_SIZEOF", "OP_ADDRESS", 
                            "OP_POINTER", "OP_CONDITIONAL1",   
                            "OP_CONDITIONAL2", NULL};
  char *diversos_lexema[] = {"sizeof", "&address", "*pointer", "?", ":", NULL};

  // contador auxiliar
  i = 0;

  // para cada lexema no vetor
  while (diversos_lexema[i]){

    // verifica se é igual ao lexema lido
    if (strcmp(lexema, diversos_lexema[i]) == 0){

      // se for lexema de POINTER ou ADDRESS
      if (strcmp(lexema, "*pointer") == 0 || strcmp(lexema, "&address") == 0){
        strcpy(result.lexema, "\0"); // reinicia lexema
        strncat(result.lexema, lexema, 1); // apenas o primeiro char vira o novo lexema
      } // end if
      
      strcpy(result.token, diversos_token[i]);
      return result; // retorna (token, lexema)
      
    } // end if
    
    i++; // incrementa contador
    
  } // end while

  ///////////////////////////////////////////
  // LITERALS E TOKENS (COM VERIFICAÇÃO DE ERROS)

  // verifica se é INT
  if (number_int(lexema) == true){

    // verifica se há ERRO
    if (error_int(lexema) == true){
      strcpy(result.token, "ERROR INT"); // há erro
    } else {
      strcpy(result.token, "LIT_INT"); // não há erro
    } // end if/else
    
    return result; // retorna (token, lexema)
    
  } // end if

  // verifica se é FLOAT
  if (number_float(lexema) == true){

    // verifica se há ERRO
    if (error_float(lexema) == true){
      strcpy(result.token, "ERROR FLOAT"); // há erro
    } else {
      strcpy(result.token, "LIT_FLOAT"); // não há erro
    } // end if/else
    
    return result; // retorna (token, lexema)
    
  } // end if

  // verifica se é CHAR
  if (lexema[0] == '\''){

    // verifica se é CHAR que necessita de '\' ou não
    if (lexema[1] == '\\'){
      if (lexema[3] == '\''){
        strcpy(result.token, "LIT_CHAR"); // não há erro
      } // end if
    } else if (lexema[2] == '\''){
      strcpy(result.token, "LIT_CHAR"); // não há erro
    } else {
      strcpy(result.token, "ERROR CHAR"); // há erro
    } // end if/else
    
    return result; // retorna (token, lexema)
    
  } // end if

  // verifica se é STRING
  if (lexema[0] == '\"'){

    // verifica se STRING está finalizada corresizeente
    if (lexema[strlen(lexema) - 1] == '\"'){
      strcpy(result.token, "LIT_STRING"); // não há erro
    } else {
      strcpy(result.token, "ERROR STRING"); // há erro
    } // end if/else
    
    return result; // retorna (token, lexema)
    
  } // end if

  ///////////////////////////////////////////
  // ID E TOKEN

  // verifica se é ID
  if (id(lexema) == true){
    strcpy(result.token, "ID");
    return result; // retorna (token, lexema)
  } // end if

  ///////////////////////////////////////////
  // ERRO DE SEPARADOR

  // contador auxiliar
  i = 0;

  // percorre o vetor com operadores
  while (op_lexema[i]){

    // verifica se há operadores na leitura
    if (strstr(lexema, op_lexema[i])){
      strcpy(result.token, "ERROR SEPARATOR"); // há erro
      return result; // retorna (token, lexema)
    } // end if
    
    i++; // incrementa contador
    
  } // end while

  ///////////////////////////////////////////
  // OUTRO ERRO
  
  strcpy(result.token, "ERROR"); // há erro
  return result; // retorna (token, lexema)

  ///////////////////////////////////////////
  
} // end analex()

// grava tokens e lexemas no arquivo de saída
void grava_token(FILE *file, token_lexema_t array[], int n){

  // inicia gravação
  printf("\nIniciando Gravação de Tokens e Lexemas...\n\n");

  // percorrre todos os (token, lexema)'s do vetor
  for (int i = 0; i < n; i++){

    // grava (token, lexema)
    fprintf(file, "%s ............... %s\n", array[i].lexema, array[i].token);
    
    // se houver ERRO
    if (strncmp(array[i].token, "ERROR", 5) == 0){

      // mostra que há erro
      fprintf(file, "\nERRO LÉXICO");
      printf("\nERRO LÉXICO\n\n");

      fclose(file); // fecha arquivo
      exit(0); // finaliza execução
      
    } // end if
    
  } // end for

  // gravação sem erros
  printf("\nGravação de Tokens e Lexemas bem sucedida!\nNão houve Erros Léxicos.\n\n");
  
} // end grava_token()

///////////////////////////////////////////

///////////////////////////////////////////
// MAIN - PROGRAMA PRINCIPAL
///////////////////////////////////////////
//int main(){
int main(int argc, char **argv) {

///////////////////////////////////////////

  // definicao do arquivo de entrada
  //char *file_name = "entrada.txt";
  char *file_name = argv[1]; // leitura do nome
  FILE *c_file = fopen(file_name, "rb");

  // inicializacao das variaveis necessárias
  char reading[100] = "\0";
  char next_char;
  char reading2[5] = "\0";
  char lines[1000][100];
  int num_lines = 0;

  // enquanto arquivo nao termina
  while(!feof(c_file)){

    // leitura do proximo char
    next_char = prox_char(c_file);

    ///////////////////////////////////////////

    // verifica se é COMENTÁRIO CURTO
    if (strncmp(reading, "//", 2) == 0){

      // verifica mudança de linha
      if (next_char == '\n'){
        strcpy(lines[num_lines], reading); // grava leitura
        strcpy(reading, "\0"); // reinicia leitura
        num_lines++; // incrementa contador
      } else {
        strncat(reading, &next_char, 1); // contatena char à leitura 
      } // end if/else
      
    } // end if

    ///////////////////////////////////////////

    // verifica se é COMENTÁRIO LONGO
    else if (strncmp(reading, "/*", 2) == 0){

      strncat(reading, &next_char, 1); // contatena char à leitura  

      // verifica fim do comentário
      if (next_char == '*' || next_char == '/'){
        
        strncat(reading2, &next_char, 1); // leitura auxiliar

        // verifica leitura auxiliar
        if (strcmp(reading2, "*/") == 0){
          strcpy(lines[num_lines], reading); // grava leitura
          strcpy(reading, "\0"); // reinicia leitura
          strcpy(reading2, "\0"); // reinicia leitura auxiliar
          num_lines++; // incrementa contador
        } // end if
        
      } // end if
      
    } // end else if

    ///////////////////////////////////////////

    // verifica se char é um separador  
    else if (next_char != '\n' && next_char != '\t' && next_char != ' '){ 

      // se char for uma pontuação
      if (pontuacao(next_char) == true){ 
        strcpy(lines[num_lines], reading); // grava leitura
        strcpy(reading, "\0"); // reinicia leitura
        num_lines++; // incrementa contador
        strncpy(lines[num_lines], &next_char, 1); // grava leitura
        num_lines++; // incrementa contador
      } // end if

      // se leitura iniciar com '&'
      else if (strncmp(reading, "&", 1) == 0){
        strcat(reading, "address"); // adiciona string
        strcpy(lines[num_lines], reading); // grava leitura
        strcpy(reading, "\0"); // reinicia leitura
        num_lines++; // incrementa contador
        strncat(reading, &next_char, 1); // concatena próximo char
      } // end else if

      // se leitura iniciar com '*'
      else if (strncmp(reading, "*", 1) == 0){
        strcat(reading, "pointer"); // adiciona string
        strcpy(lines[num_lines], reading); // grava leitura
        strcpy(reading, "\0"); // reinicia leitura
        num_lines++; // incrementa contador
        strncat(reading, &next_char, 1); // concatena próximo char
      } // end else if

      // se leitura for "sizeof"
      else if (strncmp(reading, "sizeof", 6) == 0){
        strcpy(lines[num_lines], reading); // grava leitura
        strcpy(reading, "\0"); // reinicia leitura
        num_lines++; // incrementa contador
        strncat(reading, &next_char, 1); // concatena próximo char
      } // end else if

      // adiciona char à leitura se não for separador
      else {
        strncat(reading, &next_char, 1);
      } // end else
      
    } // end else if

    // verifica se leitura está vazia
    else if (strcmp(reading, "\0") != 0){ 
      strcpy(lines[num_lines], reading); // grava leitura
      strcpy(reading, "\0"); // reinicia leitura
      num_lines++; // incrementa contador
    } // end else
    
  } // end while

  // fecha arquivo
  fclose(c_file);

///////////////////////////////////////////

  // definição de arquivo de saída para escrita
  FILE *output_file = fopen("saida.txt", "w+");

  // vetor (token, lexema)
  token_lexema_t array_result[1000];

  // contador auxiliar
  int j = 0;

  // percorre vetor de lexemas
  for (int i = 0; i < num_lines; i++){

    // se elemento for válido
    if (strcmp(lines[i],"\0") != 0 && strcmp(lines[i], " ") != 0){

      // analise léxica do elemento
      token_lexema_t result = analex(lines[i]);

      // adiciona (token, lexema) no vetor
      strcpy(array_result[j].token, result.token);
      strcpy(array_result[j].lexema, result.lexema);
      
      j++; // incrementa contador
      
    } // end if
    
  } // end for

  ///////////////////////////////////////////
  // TABELA DE SÍMBOLOS

  // criacao tabela de simbolos (ID's)
  token_lexema_t symbol_table[100];
  int table_size = 0; // número de elementos
  int broken = 0; // auxiliar

  // percorre vetor de lexemas
  for (int z = 1; z < j; z++){

    // se elemento for um ID
    if (strcmp(array_result[z].token, "ID") == 0){

      // se elemento anterior for um tipo
      if (tipo(array_result[z - 1].token) == true){

        // percorre tabela de símbolos
        for (int x = 0; x <= table_size; x++){

          broken = 0; // auxiliar

          // se não há elementos na tabela
          if (table_size == 0){
            symbol_table[x] = array_result[z]; // adiciona à tabela
            table_size++; // incrementa contador de tamanho
            broken = 1; // auxiliar
            break; // sai do loop
          } // end if

          // se o ID já existe na tabela
          else if (strcmp(symbol_table[x].lexema, array_result[z].lexema) == 0){
            strcpy(array_result[z].token, "ERROR ID ALREADY DECLARED"); // há erro
            broken = 1; // auxiliar
            break; // sai do loop
          } // end else
          
        } // end for

        // verifica auxiliar
        if (broken == 0){
          symbol_table[table_size] = array_result[z]; // adiciona à tabela
          table_size++; // incrementa contador de tamanho
        } // end if
        
      } // end if

      // se NÃO for um tipo
      else {

        // percorre tabela de símbolos
        for (int x = 0; x <= table_size; x++){

          broken = 0; // auxiliar

          // se ID foi declarado
          if (strcmp(symbol_table[x].lexema, array_result[z].lexema) == 0){
            broken = 1; // auxiliar
            break; // sai do loop
          } // end if

        } // end for

        // verifica auxiliar
        if (broken == 0){
          strcpy(array_result[z].token, "ERROR ID NOT DECLARED"); // há erro
        } // end if
        
      } // end else
      
    } // end if
    
  } // end for

  ///////////////////////////////////////////  

  // grava (token, lexema) no arquivo de saída
  grava_token(output_file, array_result, j);
 
  // fecha arquivo de saída
  fclose(output_file);
  
} // end main
