#include <malloc.h>
#include "hasse.h"


void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];
                            if ((link3.from == link2.to) && (link3.to == link1.to))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}

t_tarjan_vertex create_tarjan(int identifier)
{
    t_tarjan_vertex t = (t_tarjan_vertex)malloc(sizeof(t_tarjan_vertex));
    if (!t) {
        return NULL;
    }
    t.identifier = identifier;
    t.number = -1;
    t.access_number = -1;
    t.processing = 0;
    return t;
}

t_tarjan_vertex* createArrayTarjan(adj_list g) {
    t_tarjan_vertex t[g.size];
    for (int i = 0; i < g.size; i++) {
        t[i] = create_tarjan(i);
    }
    return t;
}

t_stack create_stack(void) {
    t_stack s;
    s.data = NULL;
    s.size = 0;
    s.capacity = 0;
    return s;
}

void push_stack(t_stack *s, int value) {
    if (s->size == s->capacity) {
        int newcap = (s->capacity == 0 ? 8 : s->capacity * 2);
        int *tmp = realloc(s->data, newcap * sizeof(int));
        if (!tmp) exit(1);
        s->data = tmp;
        s->capacity = newcap;
    }
    s->data[s->size++] = value;
}

int pop_stack(t_stack *s) {
    s->size--;
    return s->data[s->size];
}