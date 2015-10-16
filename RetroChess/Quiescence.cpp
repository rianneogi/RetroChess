#include "Engine.h"

int Engine::QuiescenceSearchStandPat(int alpha,int beta,Move lastmove)
{
	quisctime.Start();
	nodes++;
	if(nodes%1024==0)
	{
		checkup();
		//nodes = 0;
	}
	/*if(pos.getGameStatus()!=STATUS_NOTOVER)
	{
		int val = LeafEval(alpha,beta);
		if(val >= beta)
			return beta;
		else if(val < alpha)
			return alpha;
		return val;
	}*/
	int stand_pat = LeafEval(alpha,beta);
	if(stand_pat >= beta) //standpat
	{
		return beta;
	}
	if(stand_pat < alpha-PieceMaterial[PIECE_QUEEN]) //big delta pruning
	{
		return alpha;
	}
	if(alpha < stand_pat)
	{
		alpha = stand_pat;
	}
	Move m;
	int score = 0;

    vector<Move> vec; //generate moves
	vec.reserve(128);
	movegentime.Start();
	pos.generateCaptures(vec);
	movegentime.Stop();

	//vector<int> scores; //generate move scores
	//scores.reserve(128);
	//generateCaptureScores(vec, scores);

	int material = getBoardMaterial();
	for(int i = 0;i<vec.size();i++)
	{
		m = getHighestScoringMove(vec,i);
		int special = m.getSpecial();
		int captured = m.getCapturedPiece();
		if((stand_pat + PieceMaterial[getSquare2Piece(captured)] + 200 < alpha) && //delta pruning
		   (special!=PIECE_QUEEN && special!=PIECE_KNIGHT  && special!=PIECE_ROOK && special!=PIECE_BISHOP) && //not a promotion
           (material > EndgameMaterial))
		{
            continue;
		}
		if(StaticExchangeEvaluation(m.getTo(),m.getFrom(),m.getMovingPiece(),captured)<0)
			continue;
		if(!pos.makeMove(m))
		{
			continue;
		}
		ply++;
		score = -QuiescenceSearchStandPat(-beta,-alpha,m);
		pos.unmakeMove(m);
		ply--;
		if(score >= beta)
			return beta;
		if(alpha < score)
			alpha = score;
	}
	quisctime.Stop();
	return alpha;
}