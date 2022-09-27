
function PlayerScore({ index} ) {
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

function Player ( {index} ) {
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

function TeamScore({ index} ) {
  const team = useSelector(getTeam(index));
      
  return <SPlayerDataScoreRow bigger={gameResultState !== GameResultsState.FINISHED}>
    <SPlayerDataScoreRowItem 
      style={{ minWidth: 120 }} >{team.score}</SPlayerDataScoreRowItem>
  </SPlayerDataScoreRow>;
}

function Team ( {index} ) {
  const team = useSelector(getTeam(index));
  return <SPlayerItem 
    bigger={gameResultState !== GameResultsState.FINISHED}
    running={gameResultState === GameResultsState.RUNNING}>
    <SColorCircle style={{ backgroundColor:  
      '#' + ('000000' + ((team.color) >>> 0).toString(16)).slice(-6) }} />
    <SRank>{(index + 1) + '. '}</SRank>
    <div>{team.name.length > 15 ? team.name.substring(0, 15) + '...' : team.name}</div>
  </SPlayerItem>;  
}

function PlayerRotatedName ( {index} ) {
  const playerName = useSelector(getPlayerProp(index, 'playerName'));
  return <SPlayerTableHeaderItem bigger={gameResultState !== GameResultsState.FINISHED}>
    <SPlayerTableHeaderItemName bigger={gameResultState !== GameResultsState.FINISHED}>
      {playerName}</SPlayerTableHeaderItemName>
  </SPlayerTableHeaderItem> 
}

function PlayerTableField ({ rank, index }) {
  const player = useSelector(getPlayer(index));
  const player2 = useSelector(getPlayer(rank));
  /*const gameTemplate = useSelector(state => state.commonList['finishedGames']
    .list[indexInList].selectedGameTemplate);*/
  const gameTemplate = null;
  if(!player.hits) {
    return null;
  }
  if(typeof player.hits[rank] === 'undefined') {
    return 'A';
  }
  if(typeof player.hits[rank].hitsTotal === 'undefined') {
    return <SPlayerTableFieldSame bigger={gameResultState !== GameResultsState.FINISHED}/>
  }
  
  let friendlyHit = false;
  if (gameTemplate) {
    friendlyHit = (player.playerColor === player2.playerColor 
      && player.hits[rank].hitsTotal && gameTemplate.teamGame);
  }
  
  return <SPlayerTableFieldItem 
    bigger={gameResultState !== GameResultsState.FINISHED}
    style={{ ...friendlyHit ? {
                            color: '#C72C54',
                            fontWeight: 'bold',
                          } : {  } }}>
    {player.hits[rank].hitsTotal}
  </SPlayerTableFieldItem>
}

function PlayerTableFieldRow ({index, playerLength}) {
  const fields = [];
  for(let i = 0; i < playerLength; i++) {
    fields.push(<PlayerTableField index={i} rank={index}/>);
  }
  return <SPlayerTableFieldRow>
    {fields}
  </SPlayerTableFieldRow>
}

function KillLogRow({ log, colorArray, gameTime, index, opacity }) {

  let { hitsAssistance } = log;
  if (hitsAssistance) {
    // Get the most assistant player
    hitsAssistance = hitsAssistance.filter(o => o !== log.killLogWho);
    const x = _.chain(hitsAssistance).countBy();
    const y = x.toPairs().sortBy(1).reverse();
    hitsAssistance = y.map(0).value().slice(0,1);
  } else {
    hitsAssistance = [];
  }
  const whoColor = '#' + ('000000' +
    ((colorArray[log.killLogWho]) >>> 0).toString(16)).slice(-6);
  const whomColor = '#' + ('000000' +
    ((colorArray[log.killLogWhom]) >>> 0).toString(16)).slice(-6);

  const time = minuteSecondsString(gameTime * 60 -
    log.killLogTime);

  return <SKillLogRow style={{
    backgroundColor: log.bonus > 1 ? '#AE29AF': undefined,
    opacity: opacity ? (10 - index) * 0.1 : 1,
  }}>
    <SKillLogRowItem>
      {time}
    </SKillLogRowItem>
    <SKillLogRowCircle style={{ backgroundColor: whoColor }} />
    <SKillLogRowItem>
      {log.killLogWho +
      (log.bonus > 1 ? '(' + log.bonus + ')' : '') +
      (hitsAssistance.length > 0 ? ' + ' + hitsAssistance.join(', ') : '')
      }
    </SKillLogRowItem>
    <div className='base32x32icon PistolIconStyle'/>
    <SKillLogRowCircle style={{ backgroundColor: whomColor }}/>
    <SKillLogRowItem>{log.killLogWhom}</SKillLogRowItem>
  </SKillLogRow>;
}

function CountDown () {
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

function OnlinePlayerGameScore() {
  const players = useSelector(getEvaluationItem('evaluationPlayers'));
  
  return (
    <FlipMove style={{width: '100%'}} duration={750} easing='ease-out'>
      {
        players.map((player, key) => {
          return <SOnlinePlayerVis state={player.playerState} key={player.playerName}>
            <Player index={key}/>
            <PlayerScore index={key}/>
          </SOnlinePlayerVis>;
        })
      }
    </FlipMove>
  )
}

function OnlineTeamGameScore() {
  const teams = useSelector(getEvaluationItem('evaluationTeams'));
  
  return (
    <FlipMove style={{width: '100%'}} duration={750} easing='ease-out'>
      {
        teams.map((team, key) => {
          return <SOnlinePlayerVis key={team.name}>
            <Team index={key}/>
            <TeamScore index={key}/>
          </SOnlinePlayerVis>;
        })
      }
    </FlipMove>
  )
}

function Main () {
  const playerNumber = useSelector(getPlayersLength());
  const teamNumber = useSelector(getTeamsLength());
  const players = [];
  for(let i = 0; i < playerNumber; i++) {
    players.push(<Player index={i}/>);
  }
  const playerScore = [];
  for(let i = 0; i < playerNumber; i++) {
    playerScore.push(<PlayerScore key={'player_score_' + i} index={i}/>);
  }

  const playersTableHeader = [];
  if (gameResultState !== GameResultsState.RUNNING) {
    for(let i = 0; i < playerNumber; i++) {
      playersTableHeader.push(<PlayerRotatedName index={i}/>);
    }
  }
  
  const playersTableFields = [];
  if (gameResultState !== GameResultsState.RUNNING) {
    for(let i = 0; i < playerNumber; i++) {
      playersTableFields.push(<PlayerTableFieldRow index={i} playerLength={playerNumber}/>);
    }
  }
  
  const teams = [];
  for(let i = 0; i < teamNumber; i++) {
    teams.push(<Team index={i}/>);
  }
  
  const teamScore = [];
  for(let i = 0; i < teamNumber; i++) {
    teamScore.push(<TeamScore index={i}/>);
  }
  
  return <SResult style={{ color: '#fff' }}>
    {gameResultState === GameResultsState.RUNNING && <CountDown/>}
    <SContent>
      {gameResultState !== GameResultsState.RUNNING && <SPlayerMain>
        {players}
      </SPlayerMain>}
      <div>
        <SPlayerDataHeader style={{ marginLeft: gameResultState === GameResultsState.RUNNING ? 260 : undefined }}>
          <SPlayerDataHeaderItem style={{ minWidth: 80 }}>
            S
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            <div className='base24x24icon FragIconStyle'/>
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            <div className='base24x24icon SkullIconStyle'/>
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            <div className='base24x24icon HeartIconStyle'/>
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            <FontAwesomeIcon icon='walking'/>
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            <div className='base24x24icon BulletIconStyle'/>
          </SPlayerDataHeaderItem>
          <SPlayerDataHeaderItem>
            %
          </SPlayerDataHeaderItem>
        </SPlayerDataHeader>
        {gameResultState !== GameResultsState.RUNNING ? <div>{playerScore}</div> : <OnlinePlayerGameScore/>}
      </div>
      {gameResultState !== GameResultsState.RUNNING && <div>
        <SPlayerTableHeader>
          {playersTableHeader}
        </SPlayerTableHeader>
        <div style={{ marginTop: 41 }}>
          {playersTableFields}
        </div>
      </div>}
    </SContent>
    <div style={{ flex: 2 }}/>
    <SContent>
      {gameResultState !== GameResultsState.RUNNING && <SPlayerMain>
        {teams}
        <SExtremes bigger={gameResultState !== GameResultsState.FINISHED}>
          <h4>Sniper</h4>
          <div>{findExtremeByProp('playerPrecision', gameResultState).playerName}</div>
          <h4>Nepřesný</h4>
          <div>{findExtremeByProp('playerPrecision', gameResultState, true).playerName}</div>
          <h4>Běžec</h4>
          <div>{findExtremeByProp('playerFootSteps', gameResultState).playerName}</div>
          <h4>Lenoch</h4>
          <div>{findExtremeByProp('playerFootSteps', gameResultState, true).playerName}</div>
        </SExtremes>
      </SPlayerMain>}
      {teamNumber > 0 && <div>
        <SPlayerDataHeader style={{ marginLeft: gameResultState === GameResultsState.RUNNING ? 260 : undefined }}>
          <SPlayerDataHeaderItem style={{ minWidth: 120 }}>
            S
          </SPlayerDataHeaderItem>
        </SPlayerDataHeader>
        {gameResultState !== GameResultsState.RUNNING ? <div>
          {teamScore}
        </div> : <OnlineTeamGameScore/> }
      </div>}
    </SContent>
    <div style={{ flex: 2 }}/>
    {gameResultState !== GameResultsState.FRESH_FINISH && <KillLog 
      style={{
        maxHeight: '35vh',
        overflow: 'auto',
        marginTop: '31px',
        fontSize: '13px',
      }}
      view={KillLogRow}/>}
  </SResult>
}

render(<Main/>);
