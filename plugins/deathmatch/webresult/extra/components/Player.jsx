import {GameResultsState, getPlayer} from "@laser/shared-impl";
import {useSelector} from "react-redux";

export function PlayerScore({ index} ) {
  const player = useSelector(getPlayer(index));

  return <SPlayerDataScoreRow bigger={gameResultState !== GameResultsState.FINISHED}>
    <SPlayerDataScoreRowItem
      style={{ minWidth: 80 }}>{player.playerScore}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerKills}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerDeaths}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerHealth}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerFootSteps}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerAmmo}</SPlayerDataScoreRowItem>
    <SPlayerDataScoreRowItem>{player.playerPrecision}</SPlayerDataScoreRowItem>
  </SPlayerDataScoreRow>;
}

export function Player ( {index} ) {
  const player = useSelector(getPlayer(index));
  return <SPlayerItem
    running={gameResultState === GameResultsState.RUNNING}
    bigger={gameResultState !== GameResultsState.FINISHED}>
    <SColorCircle style={{ backgroundColor:
        '#' + ('000000' + ((player.playerColor) >>> 0).toString(16)).slice(-6) }} />
    <SRank>{(index + 1) + '. '}</SRank>
    <div>{player.playerName}</div>
  </SPlayerItem>;
}