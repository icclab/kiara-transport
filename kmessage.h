/* 
 * File:   kapplication.h
 * Author: aepp
 *
 * Created on 7. August 2013, 18:25
 */

#ifndef KMESSAGE_H
#define	KMESSAGE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct KIARA_MessageRaw KIARA_MessageRaw;

struct KIARA_MessageRaw
{
    char *body;
    char *service;
	char *method;
};

KIARA_MessageRaw *kmessage_parse(zframe_t *frame_content);
char *kmessage_compose(char *body, int type);

#ifdef	__cplusplus
}
#endif

#endif	/* KAPPLICATION_H */

