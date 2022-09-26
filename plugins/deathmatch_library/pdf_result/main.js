
doc.on('pageAdded', () => {
  generateHeader(doc);
})

doc.addPage({
  layout: 'landscape',
  size: 'A4',
})

doc.roundedRect(15,80, 5, doc.page.height - 140).fill('#e4e4e4');
doc.roundedRect(15,doc.page.height - 60, doc.page.width - 30, 5).fill('#e4e4e4');
doc.roundedRect(15,doc.page.height / 2 - 30, doc.page.width - 30, 5).fill('#e4e4e4');
doc.roundedRect(doc.page.width - 20,80, 5, doc.page.height - 140).fill('#e4e4e4');
doc.roundedRect(15,60, doc.page.width - 30, 10, 5).fill('#000');
doc.roundedRect(15,65, doc.page.width - 30, 15).fill('#000');
doc.font(boldText).fontSize(12).fill('#eee').text(`Datum: ${moment(game.endDate)
  .format('DD.MM.YYYY hh:mm')}`, 40, 63);

const table = new Table({
  paddingRight: 6,
  paddingLeft: 6,
  columnsNumber: 9,
  xOffset: 20,
  yOffset: 85,
  boldColumn: [2],
});
table.pushRow(['']
  .concat(['Jméno', 'Skóre', 'Tým', 'Výstřelu', 'Zabití', 'Kroky', 'Úspěšnost']));

game.result.evaluationPlayers.forEach((p, index) => {
  const player = game.playersList.find(o => o.name === p.playerName);
  table.pushRow([
    `${index + 1}.`,
    p.playerName,
    p.playerScore.toString(),
    (player && player.selectedTeam && game.selectedGameTemplate.teamGame &&  player.selectedTeam.name) || '',
    p.playerAmmo.toString(),
    p.playerKills.toString(),
    p.playerFootSteps ? p.playerFootSteps.toString() : '0',
    p.playerPrecision.toString() + ' %',
  ])
});

const tableWidth = table.generateTable(doc);

const table2 = new Table({
  paddingRight: 6,
  paddingLeft: 6,
  columnsNumber: 4,
  xOffset: 20 + tableWidth,
  yOffset: 85
});

let hits = [];
table2.pushRow(['Smrt Protihráčem', ' Smrt Spoluhráčem', 'Nejčastěji zasáhl hráče', 'Nejčastěji zasažen hráčem']);
game.result.evaluationPlayers.forEach((p, index) => {
  let newHits = [];
  let myHits = [];

  if (game.result.evaluationFinalTable) {
    const index = game.result.evaluationFinalTable.findIndex(
      item => item.playerName === p.playerName);
    game.result.evaluationFinalTable.forEach(h => {
      h.hits.forEach(h2 => {
        if (h2.hitsWho === p.playerName) {
          myHits.push({
            ...h2,
            hitsWho: h.playerName,
          })
        }
      })
    });
    game.result.evaluationPlayers.map((pl) => {
      if (game.result.evaluationFinalTable) {
        if (game.result.evaluationFinalTable[index].hits) {
          const ind = game.result.evaluationFinalTable[index].hits.findIndex(
            item => item.hitsWho === pl.playerName);
          newHits.push(game.result.evaluationFinalTable[index].hits[ind]);
        } else {
          // TODO Daniel: look why hits are not array
        }
      }
    });
    hits.push(newHits);
    myHits = myHits.sort((a, b) => (b.hitsTotal ? b.hitsTotal : 0)
      - (a.hitsTotal ? a.hitsTotal : 0));
    newHits = newHits.sort((a, b) => (b.hitsTotal ? b.hitsTotal : 0)
      - (a.hitsTotal ? a.hitsTotal : 0));
  }
  table2.pushRow([
    p.playerDeaths.toString(),
    p.playerTeamDeaths ? p.playerTeamDeaths.toString() : '0',
    myHits[0] ? myHits[0].hitsWho : '',
    newHits[0] ? newHits[0].hitsWho : '',
  ])
});
table2.generateTable(doc);

const table3 = new Table({
  paddingRight: 12,
  paddingLeft: 12,
  columnsNumber: game.result.evaluationPlayers.length + 1,
  xOffset: 20,
  yOffset: doc.page.height / 2  + 5,
  rotateHeader: true,
  boldColumn: [0],
});
table3.pushRow([''].concat(game.result.evaluationPlayers.map((p, i) => {
  const t = `${i + 1}. ${p.playerName}`;
  if (t.length > 8) {
    return t.slice(0,7) + '...'
  }
  return t;
})));

game.result.evaluationPlayers.forEach((p, index) => {
  const player = game.playersList.find(o => o.name === p.playerName);
  const array = [`${index + 1}. ${p.playerName} ${(player && player.selectedTeam &&
  game.selectedGameTemplate.teamGame && player.selectedTeam.name) ?
  ' (' + player.selectedTeam.name + ')' : ''}`];
  game.result.evaluationPlayers.forEach((p2, index2) => {
    if (index !== index2) {
      const h_ = hits[index2].find(h => h.hitsWho === p.playerName);
      array.push(h_ ? (h_.hitsTotal || 0).toString() : '')
    } else {
      array.push('-')
    }
  })
  table3.pushRow(array)
})

const table3Width = table3.generateTable(doc);

doc.roundedRect(table3Width + 40,doc.page.height / 2 - 30, 5, doc.page.height / 2 - 30).fill('#e4e4e4');

const table4 = new Table({
  paddingRight: 12,
  paddingLeft: 12,
  columnsNumber: game.result.evaluationTeams.length + 1,
  xOffset: table3Width + 40,
  yOffset: doc.page.height / 2 - 20,
  boldColumn: [1],
});

table4.pushRow(['Tým', 'Skóre']);

game.result.evaluationTeams.forEach(t => {
  table4.pushRow([
    t.name,
    t.score.toString(),
  ])
})
const table4width = game.result.evaluationTeams.length ? table4.generateTable(doc) : 0;

doc.roundedRect(table3Width + table4width + 40,
  doc.page.height / 2 - 30, 5, doc.page.height / 2 - 30).fill('#e4e4e4');

doc.roundedRect(table3Width + table4width + 40 + doc.widthOfString('a'.repeat(20)),
  doc.page.height / 2 - 30, 5, doc.page.height / 2 - 30).fill('#e4e4e4');

doc.fill('#000').font(boldText).text('SNIPER',
  table4width + table3Width + 60,
  doc.page.height / 2 - 20
).font(regularText).text(findExtremeByProp(
  game.result.evaluationPlayers, "playerPrecision").playerName)

doc.font(boldText).text('NEPŘESNÝ',
  table4width + table3Width + 60,
  doc.page.height / 2 + 10
).font(regularText).text(findExtremeByProp(
  game.result.evaluationPlayers, "playerPrecision", true).playerName)

doc.font(boldText).text('BĚŽEC',
  table4width + table3Width + 60,
  doc.page.height / 2 + 40
).font(regularText).text(findExtremeByProp(
  game.result.evaluationPlayers, "playerFootSteps").playerName)

doc.font(boldText).text('LENOCH',
  table4width + table3Width + 60,
  doc.page.height / 2 + 70
).font(regularText).text(findExtremeByProp(
  game.result.evaluationPlayers, "playerFootSteps", true).playerName)

const containerOption = {
  align: 'center',
  width: doc.page.width - table3Width - table4width - 90 - doc.widthOfString('a'.repeat(20)),
}

generateGiftVoucher(doc, containerOption);

doc.font(boldText).text('www.inlaserworld.com', doc.x,doc.page.height - 90, containerOption)
doc.moveUp();
doc.moveUp();
doc.moveUp();
doc.font(regularText).text('Děkujeme', containerOption);
doc.moveUp();
doc.moveUp();
doc.font(boldText).text('Hráli jste s vybavením IN LASER WORLD',containerOption);
doc.moveUp();
doc.moveUp();
doc.moveUp();
doc.moveUp();
doc.roundedRect(table3Width + table4width + 40 + doc.widthOfString('a'.repeat(20)),
  doc.y, containerOption.width + 30, 5).fill('#e4e4e4');
              
