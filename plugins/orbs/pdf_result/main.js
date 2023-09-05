

function generateSecondaryTable(offset, length, tableWidth) {
  const table = new Table({
    paddingRight: 6,
    paddingLeft: 6,
    columnsNumber: 4,
    xOffset: 20 + tableWidth,
    yOffset: 85
  });
  
  let hits = [];
  table.pushRow(['Smrt Protihráčem', ' Smrt Spoluhráčem', 'Nejčastěji zasáhl hráče', 'Nejčastěji zasažen hráčem']);
  game.result.evaluationPlayers.forEach((p, index) => {
    let newHits = [];
    let myHits = [];
  
    if (game.result.evaluationFinalTable ) {
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
    if(index >= offset && index < length) {
      table.pushRow([
        p.playerDeaths.toString(),
        p.playerTeamDeaths ? p.playerTeamDeaths.toString() : '0',
        myHits[0] ? myHits[0].hitsWho : '',
        newHits[0] ? newHits[0].hitsWho : '',
      ])  
    }
    
  });
  return {table, hits};
}



doc.on('pageAdded', () => {
  generateHeader(doc);
})


let pageIndex = 0;
const pageCount = Math.floor(game.result.evaluationPlayers.length / 12);
for(let i = 0; i < game.result.evaluationPlayers.length; i+=12) {
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
  doc.font(boldText).fontSize(12).fill('#eee').text(`Datum: ${moment(game.result.endDate)
    .format('DD.MM.YYYY hh:mm')}`, 40, 63);
  
  const table = generateMainTable(i, i+12);
  const tableWidth = table.generateTable(doc);
  const {table: table2, hits} = generateSecondaryTable(i, i+12, tableWidth);
  table2.generateTable(doc);
  const table3 = generateHitsTable(i,i+12, hits);
  const table3Width = table3.generateTable(doc);
  doc.roundedRect(table3Width + 40,doc.page.height / 2 - 30, 5, doc.page.height / 2 - 30).fill('#e4e4e4');
  
  let table4width_ = 0;
  let a20x = 0;
  if(pageIndex < pageCount || pageCount === 0) {
    const table4 = generateTeamTable(table3Width + 40);
  
    const table4width = game.result.evaluationTeams.length ? table4.generateTable(doc) : 0;
    table4width_ = table4width;
    a20x =doc.widthOfString('a'.repeat(20));
    
    doc.roundedRect(table3Width + table4width + 40,
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
  }
  
  const containerOption = {
    align: 'center',
    width: doc.page.width - table3Width - table4width_ - 90 - a20x,
  }
  
  if(pageCount === pageIndex) {
    if(table4width_) {
      doc.roundedRect(table3Width + table4width_ + 40 + doc.widthOfString('a'.repeat(20)),
      doc.page.height / 2 - 30, 5, doc.page.height / 2 - 30).fill('#e4e4e4');
    }
    doc.fill('#000');
    generateGiftVoucher(doc, containerOption, table3Width + table4width_ + 55 + a20x);
    doc.font(boldText).text('inlaserworld.com', doc.x,doc.page.height - 90, containerOption)
    doc.moveUp();
    doc.moveUp();
    doc.moveUp();
    doc.font(regularText).text('Děkujeme', containerOption);
    doc.moveUp();
    doc.moveUp();
    doc.moveUp();
    doc.font(boldText).text('Hráli jste s vybavením IN LASER WORLD',containerOption);
    doc.moveUp();
    doc.moveUp();
    doc.moveUp();
    doc.moveUp();
    doc.roundedRect(table3Width + table4width_ + 40 + a20x,
      doc.y, containerOption.width + 30, 5).fill('#e4e4e4');
  }
  
 
  pageIndex++;
}

