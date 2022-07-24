#include "CoreTypes.h"

const bool CT::Cell::SetCellStatus(CellStatus _cellStatus)
{
	if (cellStatus == _cellStatus) return false;
	cellStatus = _cellStatus;
	return true;
}
