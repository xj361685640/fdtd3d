#ifndef BMP_DUMPER_H
#define BMP_DUMPER_H

#include "BMPHelper.h"
#include "Dumper.h"

/**
 * Grid saver to BMP files.
 * Template class with coordinate parameter.
 */
/*
 * FIXME: get rid of duplicate code for dump of 3d, 2d and 1d grids
 */
template <class TCoord>
class BMPDumper: public Dumper<TCoord>
{
  // Helper class for usage with BMP files.
  static BMPHelper BMPhelper;

private:

  // Save grid to file for specific layer.
  void writeToFile (Grid<TCoord> &grid, GridFileType dump_type, TCoord, TCoord) const;

  // Save grid to file for all layers.
  void writeToFile (Grid<TCoord> &grid, TCoord, TCoord) const;

public:

  virtual ~BMPDumper () {}

  // Virtual method for grid loading.
  virtual void dumpGrid (Grid<TCoord> &grid, TCoord, TCoord) const CXX11_OVERRIDE;
};

/**
 * ======== Template implementation ========
 */

/**
 * Save grid to file for all layers.
 */
template <class TCoord>
void
BMPDumper<TCoord>::writeToFile (Grid<TCoord> &grid, TCoord startCoord, TCoord endCoord) const
{
  writeToFile (grid, CURRENT, startCoord, endCoord);
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
#ifdef CXX11_ENABLED
  if (GridFileManager::type == ALL)
#else
  if (this->GridFileManager::type == ALL)
#endif
  {
    writeToFile (grid, PREVIOUS, startCoord, endCoord);
  }
#if defined (TWO_TIME_STEPS)
#ifdef CXX11_ENABLED
  if (GridFileManager::type == ALL)
#else
  if (this->GridFileManager::type == ALL)
#endif
  {
    writeToFile (grid, PREVIOUS2, startCoord, endCoord);
  }
#endif /* TWO_TIME_STEPS */
#endif /* ONE_TIME_STEP || TWO_TIME_STEPS */
}

template <class TCoord>
BMPHelper BMPDumper<TCoord>::BMPhelper (PaletteType::PALETTE_BLUE_GREEN_RED, OrthogonalAxis::Z);

#endif /* BMP_DUMPER_H */
