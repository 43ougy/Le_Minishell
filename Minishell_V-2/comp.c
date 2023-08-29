int number_of_args(char *args) {
    int nb_args = 0;
    int i = 0;
    int j = 0;

    while (args[i]) {
        if (args[i] != ' ' && args[i] != '"') {
            nb_args++;
            while (args[i] != ' ' && args[i] != '"' && args[i]) {
                i++;
            }
        }
        if (args[i] == '"') {
            j = i + 1;
            while (args[j] != '"' && args[j]) {
                j++;
            }
            if (args[j] == '"') {
                if (j - i > 1) {
                    nb_args++;
                }
            }
            i = j + 1;
        }
        while (args[i] == ' ' && args[i]) {
            i++;
        }
    }
    return nb_args;
}


char **get_args(char *args, int nb_args, char **ret) {
    int i = -1;
    int j = 0;

    while (++i < nb_args) {
        int w = 0;
        int ver;
        if (args[j] == '"') {
            ver = j + 1;
            while (args[ver] != '"' && args[ver]) {
                ver++;
            }
            if (args[ver] == '"') {
                ret[i] = malloc(sizeof(char) * (ver - j - 1)); // Ajustement de la taille
                strncpy(ret[i], args + j + 1, ver - j - 1);
                ret[i][ver - j - 1] = '\0';
                j = ver + 1;
            }
        } else {
            while (args[j] != ' ' && args[j] != '"' && args[j]) {
                w++;
                j++;
            }
            ret[i] = malloc(sizeof(char) * (w + 1)); // Ajustement de la taille
            strncpy(ret[i], args + j - w, w);
            ret[i][w] = '\0';
        }
        while (args[j] == ' ' && args[j]) {
            j++;
        }
    }
    return ret;
}
