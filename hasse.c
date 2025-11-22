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


int* buildVertexToClassTable(t_partition part, int nb_vertices)
{
    int *table = (int*) malloc(nb_vertices * sizeof(int));

    for (int c = 0; c < part.size; c++) {
        t_class cls = part.lists[c];
        for (int i = 0; i < cls.size; i++) {
            int v = cls.list[i]->identifier;
            table[v] = c;
        }
    }

    return table;
}

int linkExists(t_link_array *arr, int from, int to)
{
    for (int i = 0; i < arr->log_size; i++) {
        if (arr->links[i].from == from && arr->links[i].to == to) {
            return 1;
        }
    }
    return 0;
}

t_link_array createLinkArray(t_partition part, adj_list graph)
{
    t_link_array link_array;
    link_array.log_size = 0;

    int *vertex_to_class = buildVertexToClassTable(part, graph.size);

    for (int i = 0; i < graph.size; i++) {
        int Ci = vertex_to_class[i];
        cell *cur = graph.lists[i].head;

        while (cur != NULL) {
            int j = cur->to - 1;
            int Cj = vertex_to_class[j];
            if (Ci != Cj) {
                if (!linkExists(&link_array, Ci, Cj)) {
                    if (link_array.log_size >= NBMAX) {
                        printf("Number max of links in createLinkArray\n");
                    } else {
                        link_array.links[link_array.log_size].from = Ci;
                        link_array.links[link_array.log_size].to   = Cj;
                        link_array.log_size++;
                    }
                }
            }

            cur = cur->next;
        }
    }

    free(vertex_to_class);
    return link_array;
}

void exportHasse(t_partition p, t_link_array links, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        return;
    }

    fprintf(file, "---\n");
    fprintf(file, "config:\n   layout: elk\n   theme: neo\n   look: neo\n---\n\n");
    fprintf(file, "flowchart LR\n");

    for (int i = 0; i <p.size; i++) {
        fprintf(file, "%s[{", p.lists[i].name);
        for (int j=0; j<p.lists[i].size; j++)
            fprintf(file, "%d ", p.lists[i].list[j]->identifier+1);
        fprintf(file, "}]\n");
    }
    fprintf(file, "\n");

    for (int i = 0; i < links.log_size; i++) {
        int from = links.links[i].from;
        int to = links.links[i].to;
        fprintf(file, "%s -->%s\n", p.lists[from].name, p.lists[to].name);
        printf("%s -> %s\n", p.lists[from].name, p.lists[to].name);
    }

    fclose(file);
    printf("Mermaid Hasse diagram '%s' generated successfully.\n", filename);
}

void computeClassProperties(t_partition part, t_link_array links)
{
    for (int c = 0; c < part.size; c++) {

        int hasOutgoing = 0;
        for (int i = 0; i < links.log_size; i++) {
            if (links.links[i].from == c) {
                hasOutgoing = 1;
                break;
            }
        }

        int isTransient = hasOutgoing;
        int isPersistent = !hasOutgoing;
        int isAbsorbing = (isPersistent && part.lists[c].size == 1);

        printf("%s { ", part.lists[c].name);
        for (int j=0; j<part.lists[c].size; j++)
            printf("%d ", part.lists[c].list[j]->identifier+1);
        printf("}: ");

        if (isTransient)
            printf("Transient\n");
        else
            printf("Persistent\n");

        if (isAbsorbing)
            printf("Absorbing state\n");
    }

    if (part.size == 1)
        printf("\nThe graph is irreducible \n");
    else
        printf("\nThe graph is NOT irreducible \n");
}
