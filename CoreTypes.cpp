#include "CoreTypes.h"

const bool CT::Cell::SetCellStatus(CellStatus _cellStatus)
{
	if (_cellStatus == cellStatus) return false;
	cellStatus == _cellStatus;
	return true;
}
