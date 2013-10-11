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






#include "../amge/headers.h"  

/*****************************************************************************
 *
 * builds smoother: Schwarz solver based on AE as subdomains;
 *
 ****************************************************************************/


HYPRE_Int hypre_AMGeAGSchwarzSmootherSetup(HYPRE_Int ***i_domain_dof_pointer,
				     HYPRE_Int ***j_domain_dof_pointer,
				     HYPRE_Real ***domain_matrixinverse_pointer,
				   
				     hypre_AMGeMatrixTopology **A,

				     hypre_CSRMatrix **Matrix,

				     HYPRE_Int *level_pointer,


				     HYPRE_Int *Num_elements, 

				     HYPRE_Int *Num_dofs)

{
  HYPRE_Int ierr = 0;

  HYPRE_Int i,j,l;
  HYPRE_Int level = level_pointer[0];
  HYPRE_Int **i_domain_dof, **j_domain_dof;
  HYPRE_Real **domain_matrixinverse;

  HYPRE_Int *i_AE_node, *j_AE_node;

  HYPRE_Int *i_AE_element, *j_AE_element;
  HYPRE_Int *i_element_node, *j_element_node;
			     

  i_domain_dof = hypre_CTAlloc(HYPRE_Int*, level);
  j_domain_dof = hypre_CTAlloc(HYPRE_Int*, level);
  domain_matrixinverse = hypre_CTAlloc(HYPRE_Real*, level);


  l=0;
factorization_step:
  hypre_printf("\n\nC O M P U T I N G  level[%d] SCHWARZ  S M O O T H E R\n",l);

  i_element_node = hypre_AMGeMatrixTopologyIElementNode(A[l]);
  j_element_node = hypre_AMGeMatrixTopologyJElementNode(A[l]);



  /*
  i_AE_element = hypre_AMGeMatrixTopologyIAEElement(A[l+1]);
  j_AE_element = hypre_AMGeMatrixTopologyJAEElement(A[l+1]);



  ierr = matrix_matrix_product(&i_AE_node, &j_AE_node,

			       i_AE_element, j_AE_element,
			       i_element_node, j_element_node,

			       Num_elements[l+1], 
			       Num_elements[l],
			       Num_dofs[l]);


  hypre_TFree(i_AE_element);
  hypre_TFree(j_AE_element);

  hypre_AMGeMatrixTopologyIAEElement(A[l+1]) = NULL;
  hypre_AMGeMatrixTopologyJAEElement(A[l+1]) = NULL;



  i_domain_dof[l] = i_AE_node;
  j_domain_dof[l] = j_AE_node;

  */


  i_domain_dof[l] = i_element_node;
  j_domain_dof[l] = j_element_node;
 

  /*
  ierr = hypre_ComputeSchwarzSmoother(i_domain_dof[l],
				      j_domain_dof[l],
				      Num_elements[l+1],

				      Matrix[l],

				      &domain_matrixinverse[l]);
				      */

  ierr = hypre_ComputeSchwarzSmoother(i_domain_dof[l],
				      j_domain_dof[l],
				      Num_elements[l],

				      Matrix[l],

				      &domain_matrixinverse[l]);
  l++;
  
  if (l < level && Num_dofs[l] > 0) goto factorization_step;
 
  level = l;


  *i_domain_dof_pointer = i_domain_dof;
  *j_domain_dof_pointer = j_domain_dof;
  *domain_matrixinverse_pointer = domain_matrixinverse;

  *level_pointer = level;

  return ierr;

}


 
