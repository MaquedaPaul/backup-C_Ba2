
#ifndef UTILS_H_
#define UTILS_H_

#include <commons/config.h>
#include <stdint.h> //Distintos tipos de INT
#include <stdio.h>  //Para incluir NULL
bool config_has_all_properties(t_config *cfg, char **properties);
#endif
