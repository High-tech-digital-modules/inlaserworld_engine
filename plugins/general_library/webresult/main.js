const SResult = styled.div`
  display: flex;
  flex-direction: row;
  margin-top: 30px;
  padding: 15px;
  color: #fff;
`

const SPlayerMain = styled.div`
  margin-top: 41px;
`

const SContent = styled.div`
  display: flex;
  flex-direction: row;
`

const SPlayerDataHeader = styled.div`
  display: flex;
  flex-direction: row;
  margin-bottom: 10px;
`

const SPlayerDataHeaderItem = styled.div`
  text-align: center;
  min-width: 60px;
  color: #7F8489;
  font-size: 22px;
`

const SPlayerDataScoreRow = styled.div`
  display: flex;
  flex-direction: row;
  height: ${props => props.bigger ? '40px' : '26px'} ;
  font-size: ${props => props.bigger ? '22px' : '16px'} ;
  align-items: center;
  &:nth-child(odd) {
    background-color: #2D3034;
  }
`

const SPlayerDataScoreRowItem = styled.div`
  text-align: center;
  min-width: 60px;
`

const SPlayerItem = styled.div`
  display: flex;
  flex-direction: row;
  align-items: center;
  padding: 0px 10px;
  min-width: ${props => props.running ? '260px' : '0px'} ;
  font-size: ${props => props.bigger ? '22px' : '16px'} ;
  height: ${props => props.bigger ? '40px' : '26px'} ;
  &:nth-child(odd) {
    background-color: ${props => !props.running ? '#2D3034' : 'transparent'};
  }
`
const SColorCircle = styled.div`
  width: 15px;
  height: 15px;
  border-radius: 50%;
  cursor: pointer;
  margin-right: 10px;
`
const SRank = styled.div`
  min-width: 30px;
`

const SPlayerTableHeader = styled.div`
  display: flex;
  flex-direction: row;
`

const SPlayerTableHeaderItem = styled.div`
  position: relative;
  width: ${props => props.bigger ? '50px' : '35px'} ;
`

const SPlayerTableHeaderItemName = styled.div`
  position: absolute;
  font-size: ${props => props.bigger ? '18px' : '12px'} ;
  top: 15px;
  left: 6px;
  transform: rotate(-45deg);
  transform-origin: 0% 0%;
  text-overflow: ellipsis;
  width: 70px;
  overflow: hidden;
`

const SPlayerTableFieldRow = styled.div`
  display: flex;
  flex-direction: row;
  &:nth-child(odd) {
    background-color: #2D3034;
  }
`

const SPlayerTableFieldSame = styled.div`
  width: ${props => props.bigger ? '50px' : '35px'} ;
  height: ${props => props.bigger ? '40px' : '26px'} ;
  background-color: #494c52;
`

const SPlayerTableFieldItem = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  width: ${props => props.bigger ? '50px' : '35px'} ;
  height: ${props => props.bigger ? '40px' : '26px'} ;
  font-size: ${props => props.bigger ? '22px' : '16px'} ;
  border-right: 1px solid #2D3034;
  cursor: pointer;
  &:hover {
    background-color: #45CBF7;
  }
`

const SExtremes = styled.div`
  margin-top: 20px;
  font-size: ${props => props.bigger ? '20px' : '14px'} ;
  h4 {
    font-size: ${props => props.bigger ? '14px' : '12px'} ;
    font-weight: bold;
    color: #7F8489;
    margin-bottom: 2px;
  }
`

const SKillLogRow = styled.div`
  display: flex;
  flex-direction: row;
  align-items: center;
`

const SKillLogRowItem = styled.div`
  margin: 0px 5px;
`

const SKillLogRowCircle = styled.div`
  width: 15px;
  height: 15px;
  border-radius: 50%;
  margin: 0px 10px;
`

const SGameProgress = styled.div`
  align-items: center;
  display: flex;
  width: 180px;
  height: 180px;
  color: #fff;
  margin-top: 31px;
  margin-right: 20px;
`

const SOnlinePlayerVis = styled.div`
  display: flex;
  flex-direction: row;
  font-size: 28px;
  align-items: center;
  &:nth-child(odd) {
    background-color: #2D3034;
  }
  background: linear-gradient(to top left,
              rgba(0, 0, 0, 0) 0%,
              rgba(0, 0, 0, 0) calc(50% - 2.8px),
              rgba(199, 44, 84, ${props => props.state ===  PlayerGameState.DEAD ? 1 
                : (props.state ===  PlayerGameState.REVIVAL ? 0.4 : 0)}) 50%,
              rgba(0, 0, 0, 0) calc(50% + 2.8px),
              rgba(0, 0, 0, 0) 100%) no-repeat;
`