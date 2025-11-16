#include <malloc.h>
#include "hasse.h"


/*void removeTransitiveLinks(t_link_array *p_link_array)
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
}*/

t_tarjan_vertex create_tarjan(int identifier)
{
    t_tarjan_vertex t;
    t.identifier = identifier;
    t.number = -1;
    t.access_number = -1;
    t.processing = 0;
    return t;
}

t_tarjan_vertex* createTarjanArray(adj_list g) {
    t_tarjan_vertex* t = (t_tarjan_vertex*) malloc(g.size * sizeof(t_tarjan_vertex));
    for (int i = 0; i < g.size; i++) {
        t[i] = create_tarjan(i);
    }
    return t;
}

t_stack create_stack() {
    t_stack s;
    s.size = 0;
    return s;
}

void push_stack(t_stack *s, t_tarjan_vertex * val) {
    if (s->size >= NBMAX) {
        printf("max. stack size reached");
    } else {
        s->data[s->size] = val;
        s->size++;
    }
}

t_tarjan_vertex * pop_stack(t_stack *s) {
    if (s->size == 0) return NULL;
    s->size--;
    return s->data[s->size];
}

void parcours(t_tarjan_vertex* v, int * number, t_stack * s, adj_list g, t_tarjan_vertex * arr, t_partition * p) {
    v->number = *number;
    v->access_number = *number;
    (*number) ++;
    push_stack(s, v);
    v->processing = 1;

    list successors = g.lists[v->identifier];
    cell * cur = successors.head;
    while (cur!=NULL) {
        t_tarjan_vertex* w = &arr[cur->to-1];
        if (w->number == -1) {
            parcours(w, number, s, g, arr, p);
            if (v->access_number > w->access_number) v->access_number = w->access_number;
        }
        else if (w->processing) {
            if (v->access_number > w->number) v->access_number = w->number;
        }
        cur = cur->next;
    }
    if (v->access_number == v->number) {
        t_class c;
        c.name[0] = 'C';
        c.name[1] = '0' + (p->size + 1) ;
        c.name[2] = '\0';
        c.size = 0;
        c.list = (t_tarjan_vertex**) malloc(g.size * sizeof(t_tarjan_vertex*));
        t_tarjan_vertex* w;
        do {
            w = pop_stack(s);
            w->processing = 0;
            c.list[c.size ++] = w;
        } while (w != v);
        p->lists[p->size++] = c;
    }
}

t_partition tarjan(adj_list g) {
    int num = 0;
    t_stack s = create_stack();
    t_partition p;
    p.size = 0;
    p.lists = (t_class *) malloc(NBMAX * sizeof(t_class));
    t_tarjan_vertex * allVertex = createTarjanArray(g);

    parcours(&allVertex[0], &num, &s, g, allVertex, &p);

    for (int i=1; i<g.size; i++) {
        if (allVertex[i].number == -1) parcours(&allVertex[i], &num, &s, g, allVertex, &p);
    }

    return p;
}