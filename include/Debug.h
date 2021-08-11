#pragma once

#ifdef Debug
    #define PRINT(file, msg)        fprintf(file, "%3d (%10s): %s\n",      __LINE__, __func__, msg)
    #define PRINTSTR(msg)           fprintf(stdout, "%3d (%10s): \"%s\" -> \"%s\"\n",  __LINE__, __func__, #msg, msg)

    #define PRINTVAL(file, labl)    fprintf(file, "%3d (%10s): \"%s\" -> %d\n", __LINE__, __func__, #labl, labl)
    #define DEBUG(labl)             PRINTVAL(stdout, labl)
    #define ERROR(labl)             PRINTVAL(stderr, labl)
    #define LOG(msg)                PRINT(stdout, #msg)
    #define ERR(msg)                PRINT(stderr, #msg)
#endif
#ifndef Debug
    #define PRINT(msg, file)
    #define PRINTSTR(msg)
    
    #define PRINTVAL(file, labl)
    #define DEBUG(labl)
    #define ERROR(labl)
    #define LOG(msg)
    #define ERR(msg)
#endif

// Utilizzo:
//  LOG(stringa da stampare su stdout senza apici);
//  ERR(stringa da stampare su stderr senza apici);
//  DEBUG(variabile di cui stampare il contenuto);

//ex:
//    (comando) --> (su stdout)
//    (comando) ++> (su stderr)
//  LOG(stringa di messaggio);  --> "<numero riga>: stringa di messaggio\n"
//  ERR(stringa di errore);     ++> "<numero riga>: stringa di errore\n"
//  DEBUG(variabile);           --> "<numero riga>: "nome_variabile" -> valore_variabile\n"   (solo con int)