#include "ParallelYeeGridLayout.h"

#ifdef PARALLEL_GRID

/**
 * Identify size of grid for current computational node
 */
#if defined (PARALLEL_BUFFER_DIMENSION_1D_X) || defined (PARALLEL_BUFFER_DIMENSION_1D_Y) || defined (PARALLEL_BUFFER_DIMENSION_1D_Z)
void
ParallelYeeGridLayout::CalculateGridSizeForNode (grid_coord &c1, grid_coord &core1, int nodeGridSize1, bool has1, grid_coord size1) const
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X || PARALLEL_BUFFER_DIMENSION_1D_Y || PARALLEL_BUFFER_DIMENSION_1D_Z) */
#if defined (PARALLEL_BUFFER_DIMENSION_2D_XY) || defined (PARALLEL_BUFFER_DIMENSION_2D_YZ) || defined (PARALLEL_BUFFER_DIMENSION_2D_XZ)
void
ParallelYeeGridLayout::CalculateGridSizeForNode (grid_coord &c1, grid_coord &core1, int nodeGridSize1, bool has1, grid_coord size1,
                                                 grid_coord &c2, grid_coord &core2, int nodeGridSize2, bool has2, grid_coord size2) const
#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY || PARALLEL_BUFFER_DIMENSION_2D_YZ || PARALLEL_BUFFER_DIMENSION_2D_XZ */
#if defined (PARALLEL_BUFFER_DIMENSION_3D_XYZ)
void
ParallelYeeGridLayout::CalculateGridSizeForNode (grid_coord &c1, grid_coord &core1, int nodeGridSize1, bool has1, grid_coord size1,
                                                 grid_coord &c2, grid_coord &core2, int nodeGridSize2, bool has2, grid_coord size2,
                                                 grid_coord &c3, grid_coord &core3, int nodeGridSize3, bool has3, grid_coord size3) const
#endif /* PARALLEL_BUFFER_DIMENSION_3D_XYZ */
{
#if defined (PARALLEL_BUFFER_DIMENSION_1D_X) || defined (PARALLEL_BUFFER_DIMENSION_1D_Y) || defined (PARALLEL_BUFFER_DIMENSION_1D_Z) || \
    defined (PARALLEL_BUFFER_DIMENSION_2D_XY) || defined (PARALLEL_BUFFER_DIMENSION_2D_YZ) || defined (PARALLEL_BUFFER_DIMENSION_2D_XZ) || \
    defined (PARALLEL_BUFFER_DIMENSION_3D_XYZ)
  core1 = size1 / nodeGridSize1;

  if (has1)
  {
    c1 = core1;
  }
  else
  {
    c1 = size1 - (nodeGridSize1 - 1) * (size1 / nodeGridSize1);
  }
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X || PARALLEL_BUFFER_DIMENSION_1D_Y || PARALLEL_BUFFER_DIMENSION_1D_Z) ||
          PARALLEL_BUFFER_DIMENSION_2D_XY || PARALLEL_BUFFER_DIMENSION_2D_YZ || PARALLEL_BUFFER_DIMENSION_2D_XZ) ||
          PARALLEL_BUFFER_DIMENSION_3D_XYZ */

#if defined (PARALLEL_BUFFER_DIMENSION_2D_XY) || defined (PARALLEL_BUFFER_DIMENSION_2D_YZ) || defined (PARALLEL_BUFFER_DIMENSION_2D_XZ) || \
    defined (PARALLEL_BUFFER_DIMENSION_3D_XYZ)
  core2 = size2 / nodeGridSize2;

  if (has2)
  {
    c2 = core2;
  }
  else
  {
    c2 = size2 - (nodeGridSize2 - 1) * (size2 / nodeGridSize2);
  }
#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY || PARALLEL_BUFFER_DIMENSION_2D_YZ || PARALLEL_BUFFER_DIMENSION_2D_XZ) ||
          PARALLEL_BUFFER_DIMENSION_3D_XYZ */

#if defined (PARALLEL_BUFFER_DIMENSION_3D_XYZ)
  core3 = size3 / nodeGridSize3;

  if (has3)
  {
    c3 = core3;
  }
  else
  {
    c3 = size3 - (nodeGridSize3 - 1) * (size3 / nodeGridSize3);
  }
#endif /* PARALLEL_BUFFER_DIMENSION_3D_XYZ */
} /* ParallelYeeGridLayout::CalculateGridSizeForNode */

#ifdef GRID_1D

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord core1;

  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX ());

  sizeForCurNode = GridCoordinate1D (core1);
  coreSizePerNode = GridCoordinate1D (c1);
} /* ParallelYeeGridLayout::Initialize */

#endif /* GRID_1D */

#ifdef GRID_2D

#if defined (PARALLEL_BUFFER_DIMENSION_1D_X) || defined (PARALLEL_BUFFER_DIMENSION_1D_Y)

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord c2;

  grid_coord core1;
  grid_coord core2;

#ifdef PARALLEL_BUFFER_DIMENSION_1D_X
  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX ());
  core2 = size.getY ();
  c2 = core2;
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X */

#ifdef PARALLEL_BUFFER_DIMENSION_1D_Y
  core1 = size.getX ();
  c1 = core1;
  CalculateGridSizeForNode (c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY ());
#endif /* PARALLEL_BUFFER_DIMENSION_1D_Y */

  sizeForCurNode = GridCoordinate2D (core1, core2);
  coreSizePerNode = GridCoordinate2D (c1, c2);
} /* ParallelYeeGridLayout::Initialize */

#endif /* PARALLEL_BUFFER_DIMENSION_1D_X || PARALLEL_BUFFER_DIMENSION_1D_Y */

#ifdef PARALLEL_BUFFER_DIMENSION_2D_XY

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord c2;

  grid_coord core1;
  grid_coord core2;

  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX (),
                            c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY ());

  sizeForCurNode = GridCoordinate2D (core1, core2);
  coreSizePerNode = GridCoordinate2D (c1, c2);
} /* ParallelYeeGridLayout::Initialize */

#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY */

#endif /* GRID_2D */

#ifdef GRID_3D

#if defined (PARALLEL_BUFFER_DIMENSION_1D_X) || \
    defined (PARALLEL_BUFFER_DIMENSION_1D_Y) || \
    defined (PARALLEL_BUFFER_DIMENSION_1D_Z)

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord c2;
  grid_coord c3;

  grid_coord core1;
  grid_coord core2;
  grid_coord core3;

#ifdef PARALLEL_BUFFER_DIMENSION_1D_X
  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX ());
  core2 = size.getY ();
  c2 = core2;
  core3 = size.getZ ();
  c3 = core3;
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X */

#ifdef PARALLEL_BUFFER_DIMENSION_1D_Y
  core1 = size.getX ();
  c1 = core1;
  CalculateGridSizeForNode (c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY ());
  core3 = size.getZ ();
  c3 = core3;
#endif /* PARALLEL_BUFFER_DIMENSION_1D_Y */

#ifdef PARALLEL_BUFFER_DIMENSION_1D_Z
  core1 = size.getX ();
  c1 = core1;
  core2 = size.getY ();
  c2 = core2;
  CalculateGridSizeForNode (c3,
                            core3,
                            parallelGridCore.getNodeGridSizeZ (),
                            parallelGridCore.getHasF (),
                            size.getZ ());
#endif /* PARALLEL_BUFFER_DIMENSION_1D_Z */

  sizeForCurNode = GridCoordinate3D (core1, core2, core3);
  coreSizePerNode = GridCoordinate3D (c1, c2, c3);
} /* ParallelYeeGridLayout::Initialize */

#endif /* PARALLEL_BUFFER_DIMENSION_1D_X || PARALLEL_BUFFER_DIMENSION_1D_Y || PARALLEL_BUFFER_DIMENSION_1D_Z */

#if defined (PARALLEL_BUFFER_DIMENSION_2D_XY) || \
    defined (PARALLEL_BUFFER_DIMENSION_2D_YZ) || \
    defined (PARALLEL_BUFFER_DIMENSION_2D_XZ)

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord c2;
  grid_coord c3;

  grid_coord core1;
  grid_coord core2;
  grid_coord core3;

#ifdef PARALLEL_BUFFER_DIMENSION_2D_XY
  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX (),
                            c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY ());
  core3 = size.getZ ();
  c3 = core3;
#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY */

#ifdef PARALLEL_BUFFER_DIMENSION_2D_YZ
  core1 = size.getX ();
  c1 = core1;
  CalculateGridSizeForNode (c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY (),
                            c3,
                            core3,
                            parallelGridCore.getNodeGridSizeZ (),
                            parallelGridCore.getHasF (),
                            size.getZ ());
#endif /* PARALLEL_BUFFER_DIMENSION_2D_YZ */

#ifdef PARALLEL_BUFFER_DIMENSION_2D_XZ
  core2 = size.getY ();
  c2 = core2;
  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX (),
                            c3,
                            core3,
                            parallelGridCore.getNodeGridSizeZ (),
                            parallelGridCore.getHasF (),
                            size.getZ ());
#endif /* PARALLEL_BUFFER_DIMENSION_2D_XZ */

  sizeForCurNode = GridCoordinate3D (core1, core2, core3);
  coreSizePerNode = GridCoordinate3D (c1, c2, c3);
} /* ParallelYeeGridLayout::Initialize */

#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY || PARALLEL_BUFFER_DIMENSION_2D_YZ || PARALLEL_BUFFER_DIMENSION_2D_XZ */

#ifdef PARALLEL_BUFFER_DIMENSION_3D_XYZ

/**
 * Initialize size of grid per node
 */
void
ParallelYeeGridLayout::Initialize (const ParallelGridCore &parallelGridCore) /**< out: size of grid for node, except
                                                                              *   the node at the right border which
                                                                              *   is assigned all the data which is left
                                                                              *   after equal spread for all nodes.
                                                                              *   Thus, for all nodes except node at the
                                                                              *   right border core and returned sizes
                                                                              *   are the same */
{
  grid_coord c1;
  grid_coord c2;
  grid_coord c3;

  grid_coord core1;
  grid_coord core2;
  grid_coord core3;

  CalculateGridSizeForNode (c1,
                            core1,
                            parallelGridCore.getNodeGridSizeX (),
                            parallelGridCore.getHasR (),
                            size.getX (),
                            c2,
                            core2,
                            parallelGridCore.getNodeGridSizeY (),
                            parallelGridCore.getHasU (),
                            size.getY (),
                            c3,
                            core3,
                            parallelGridCore.getNodeGridSizeZ (),
                            parallelGridCore.getHasF (),
                            size.getZ ());

  sizeForCurNode = GridCoordinate3D (core1, core2, core3);
  coreSizePerNode = GridCoordinate3D (c1, c2, c3);
} /* ParallelYeeGridLayout::Initialize */

#endif /* PARALLEL_BUFFER_DIMENSION_3D_XYZ */

#endif /* GRID_3D */

ParallelGridCoordinate
ParallelYeeGridLayout::getEpsSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getMuSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getExSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getEySizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getEzSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHxSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHySizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHzSizeForCurNode () const
{
  return getSizeForCurNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getEpsCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getMuCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getExCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getEyCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getEzCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHxCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHyCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

ParallelGridCoordinate
ParallelYeeGridLayout::getHzCoreSizePerNode () const
{
  return getCoreSizePerNode ();
}

#endif /* PARALLEL_GRID */
