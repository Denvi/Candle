#ifndef FORMTOCONFIGURATIONTRANSFORMER_H
#define FORMTOCONFIGURATIONTRANSFORMER_H

#include "config/configuration.h"
#include "../frmsettings.h"

class FormToConfigurationTransformer
{
public:
    FormToConfigurationTransformer();

    static Configuration transformToConfiguration(frmSettings *form);
    static void transformToForm(frmSettings *form, Configuration *configuration);
};

#endif // FORMTOCONFIGURATIONTRANSFORMER_H
