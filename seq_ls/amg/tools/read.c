/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/





/******************************************************************************
 *
 * Read routines
 *
 *****************************************************************************/

#include "io.h"


/*--------------------------------------------------------------------------
 * ReadYSMP
 *--------------------------------------------------------------------------*/

hypre_Matrix   *ReadYSMP(file_name)
char     *file_name;
{
   hypre_Matrix  *matrix;

   FILE    *fp;

   HYPRE_Real  *data;
   HYPRE_Int     *ia;
   HYPRE_Int     *ja;
   HYPRE_Int      size;
   
   HYPRE_Int      j;


   /*----------------------------------------------------------
    * Read in the data
    *----------------------------------------------------------*/

   fp = fopen(file_name, "r");

   hypre_fscanf(fp, "%d", &size);

   ia = hypre_TAlloc(HYPRE_Int, hypre_NDIMU(size+1));
   for (j = 0; j < size+1; j++)
      hypre_fscanf(fp, "%d", &ia[j]);

   ja = hypre_TAlloc(HYPRE_Int, hypre_NDIMA(ia[size]-1));
   for (j = 0; j < ia[size]-1; j++)
      hypre_fscanf(fp, "%d", &ja[j]);

   data = hypre_TAlloc(HYPRE_Real, hypre_NDIMA(ia[size]-1));
   for (j = 0; j < ia[size]-1; j++)
      hypre_fscanf(fp, "%le", &data[j]);

   fclose(fp);

   /*----------------------------------------------------------
    * Create the matrix structure
    *----------------------------------------------------------*/

   matrix = hypre_NewMatrix(data, ia, ja, size);

   return matrix;
}

/*--------------------------------------------------------------------------
 * ReadVec
 *--------------------------------------------------------------------------*/

hypre_Vector   *ReadVec(file_name)
char     *file_name;
{
   hypre_Vector  *vector;

   FILE    *fp;

   HYPRE_Real  *data;
   HYPRE_Int      size;
   
   HYPRE_Int      j;


   /*----------------------------------------------------------
    * Read in the data
    *----------------------------------------------------------*/

   fp = fopen(file_name, "r");

   hypre_fscanf(fp, "%d", &size);

   data = hypre_TAlloc(HYPRE_Real, hypre_NDIMU(size));
   for (j = 0; j < size; j++)
      hypre_fscanf(fp, "%le", &data[j]);

   fclose(fp);

   /*----------------------------------------------------------
    * Create the vector structure
    *----------------------------------------------------------*/

   vector = hypre_NewVector(data, size);

   return vector;
}

