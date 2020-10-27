/*****************************************************************************
 * attachment.c: Input attachments
 *****************************************************************************
 * Copyright (C) 1999-2020 VLC authors and VideoLAN
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>
#include <vlc_input.h>

void vlc_input_attachment_Delete( input_attachment_t *a )
{
    if( !a )
        return;

    free( a->p_data );
    free( a->psz_description );
    free( a->psz_mime );
    free( a->psz_name );
    free( a );
}

input_attachment_t *vlc_input_attachment_New( const char *psz_name,
                                              const char *psz_mime,
                                              const char *psz_description,
                                              const void *p_data,
                                              size_t i_data )
{
    input_attachment_t *a = (input_attachment_t *)malloc( sizeof (*a) );
    if( unlikely(a == NULL) )
        return NULL;

    a->psz_name = strdup( psz_name ? psz_name : "" );
    a->psz_mime = strdup( psz_mime ? psz_mime : "" );
    a->psz_description = strdup( psz_description ? psz_description : "" );
    a->i_data = i_data;
    a->p_data = malloc( i_data );
    if( i_data > 0 && likely(a->p_data != NULL) )
        memcpy( a->p_data, p_data, i_data );

    if( unlikely(a->psz_name == NULL || a->psz_mime == NULL
              || a->psz_description == NULL || (i_data > 0 && a->p_data == NULL)) )
    {
        vlc_input_attachment_Delete( a );
        a = NULL;
    }
    return a;
}

input_attachment_t *vlc_input_attachment_Duplicate( const input_attachment_t *a )
{
    return vlc_input_attachment_New( a->psz_name, a->psz_mime, a->psz_description,
                                     a->p_data, a->i_data );
}
