#include "../include/utils.h"

bool config_has_all_properties(t_config *cfg, char **properties)
{
    for (uint8_t i = 0; properties[i] != NULL; i++)
    {
        if (!config_has_property(cfg, properties[i]))
            return false;
    }
    return true;
}

void cortarPrimerElementoDeUnaListaYPegarloEnOtra(t_list *unaLista, t_list *otraLista)
{
    if (!unaListaEstaVacia(unaLista))
    {
        list_add(otraLista, list_remove(unaLista, 0));
    }
}
bool unaListaEstaVacia(t_list *unaLista)
{
    return list_is_empty(unaLista);
}