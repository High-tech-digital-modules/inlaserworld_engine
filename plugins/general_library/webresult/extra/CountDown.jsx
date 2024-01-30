import {getEvaluationItem} from "@laser/shared-impl";
import {useSelector} from "react-redux";
import CircularProgressbar from "react-circular-progressbar";
import {minuteSecondsString} from "@laser/types";


export default function CountDown () {
  const evaluationGameTime = useSelector(getEvaluationItem('evaluationGameTime'));
  const evaluationState = useSelector(getEvaluationItem('evaluationState'));
  const gameTime = useSelector(getEvaluationItem('gameTime'));
  const barColor = evaluationState === 3 ? '244, 169, 65' : '174, 41, 175';
  return <SGameProgress>
    <CircularProgressbar
      counterClockwise={true}
      strokeWidth={14}
      styles={{
        path: { stroke: `rgba(${barColor}, ${evaluationGameTime * 100 /
          (gameTime * 60)})`, strokeWidth: 8 },
        text: { fill: '#fff', fontSize: '16px' },
        trail: { stroke: '#282C31', strokeWidth: 14 },
      }}
      percentage={evaluationGameTime * 100 /
        (gameTime * 60)}
      text={minuteSecondsString(evaluationGameTime)}
    />
  </SGameProgress>;
}