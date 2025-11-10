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
    t_tarjan_vertex t;
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

void parcours(t_tarjan_vertex* v, int * number, t_stack * p, adj_list g, t_tarjan_vertex arr[]) {
    v->number = *number;
    v->access_number = *number;
    (*number) ++;
    push_stack(p, v);
    v->processing = 1;

    list successors = g.lists[v->identifier];
    cell * cur = successors.head;
    while (cur!=NULL) {
        t_tarjan_vertex* w = &arr[cur->to];
        if (w->number == -1) {
            parcours(w, number, p, g, arr);
            if (v->access_number > w->access_number) v->access_number = w->access_number;
        }
        else if (w->processing) {
            if (v->access_number > w->number) v->access_number = w->number;
        }
        cur = cur->next;
    }
    if (v->access_number == v->number) {
        t_class c;
        c.name = "C";
        c.list.size = 0;
        c.list.head;
        t_tarjan_vertex w;
        do {
            w = pop_stack(p);
            w.processing = 0;
            //add w to C
        } while (w.identifier != v->identifier);
        //add c to partition

    }
}