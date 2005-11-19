/*   $OSSEC, decoder.c, v0.1, 2005/06/21, Daniel B. Cid$   */

/* Copyright (C) 2005 Daniel B. Cid <dcid@ossec.net>
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */


/* v0.1: 2005/06/21
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os_regex/os_regex.h"
#include "os_xml/os_xml.h"

#include "shared.h"

#include "eventinfo.h"
#include "decoder.h"




/* DecodeEvent.
 * Will use the plugins to decode the received event.
 */
void DecodeEvent(Eventinfo *lf)
{
    PluginNode *node;
    PluginNode *child_node;
    PluginInfo *nnode;
    
    node = OS_GetFirstPlugin();
    
    /* Return if no node...
     * This shouldn't happen here anyways
     */
    if(!node)
        return;
  
    
    do 
    {
        if(node->plugin)
        {
            nnode = node->plugin;
           
            merror("going on prematch:%s", nnode->prematch);
            
            /* If prematch fails, go to the next plugin in the list */
            if(!nnode->prematch || !OS_Regex(nnode->prematch,lf->log))
                continue;

            lf->log_tag = nnode->name;

            child_node = node->child;
            merror("tag: %s - log: %s",lf->log_tag, lf->log);


            /* Check if we have any child plugin */
            while(child_node)
            {
                nnode = child_node->plugin;

                merror("child found: %s", nnode->prematch);
                
                if(nnode->prematch && OS_Regex(nnode->prematch,lf->log))
                {
                    merror("regex found");
                    break;
                }
                
                child_node = child_node->next;
                nnode = NULL;
            }
           
            if(!nnode)
                return;

            merror("node not null");
            
            /* Getting the regex */
            if(nnode->regex)
            {
                int i = 0;
                char **fields;
                
                merror("nnode->regex: %s, lf->log: %s,",nnode->regex,lf->log);
                fields = OS_RegexStr(nnode->regex,lf->log);
                if(!fields)
                    return;

                merror("found");
                while(fields[i])
                {
                    merror("order i: %s", nnode->order[i]);
                    if(nnode->order[i])
                    {
                        /* DstUser field */
                        if(strcmp(nnode->order[i],"dstuser") == 0)
                        {
                            lf->dstuser = fields[i];
                            i++;
                            continue;
                        }
                         /* User field */
                        else if(strcmp(nnode->order[i],"user") == 0)
                        {
                            lf->user = fields[i];
                            i++;
                            continue;
                        }
                        /* srcip */
                        else if(strcmp(nnode->order[i],"srcip") == 0)
                        {
                            lf->srcip = fields[i];
                            i++;
                            continue;
                        }
                        /* desip */
                        else if(strcmp(nnode->order[i],"dstip") == 0)
                        {
                            lf->dstip = fields[i];
                            i++;
                            continue;
                        }
                        /* ID */
                        else if(strcmp(nnode->order[i],"id") == 0)
                        {
                            lf->id = fields[i];
                            i++;
                            continue;
                        }
                        
                        /* We do not free any memory used above */
                    }
                    
                    free(fields[i]);
                    i++;
                }

                free(fields);
                    
            }
           
            
            /* Checking if the FTS is set */
            if(nnode->fts)
            {
                lf->fts = nnode->fts;

                /* the comment we need to duplicate too */
                if(nnode->ftscomment)
                    lf->comment = nnode->ftscomment;
            }

            
            /* Matched the pre match */
            return;         
        }
       
       merror("next!"); 
    }while((node=node->next) != NULL);
}
    

/* EOF */
