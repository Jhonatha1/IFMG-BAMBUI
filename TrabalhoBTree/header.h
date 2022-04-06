/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "serializable.h"


class header : public serializable {
   public:
      header();
      header(const string t, unsigned int v);
      header(const header &h);
      virtual ~header();
      header operator=(const header &h);
      bool operator==(const header &h);
      unsigned long long int getFirstDeleted() const;
      void setFirstDeleted(unsigned long long int r);
      unsigned long long int getFirstValid() const;
      void setFirstValid(unsigned long long int r);
      string getType() const;
      void setType(string t);
      unsigned int getVersion() const;
      void setVersion(unsigned int v);
      virtual string toString();
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
   protected:
      string type;
      unsigned int version;
      unsigned long long int firstValid;
      unsigned long long int firstDeleted;
};

#endif // HEADER_H_INCLUDED
