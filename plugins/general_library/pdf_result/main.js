function generateHeader(doc) {
  const options = {
    width: doc.page.width - 40,
    align: 'right'
  }
  doc.font(regularText).fontSize(6).text('Tel: +420 734 876 767',15, 20, options)
    .text('Email: info@zabavahornik.cz', options)
    .text('Web: www.zabavahornik.cz', options)
    .text('FB: www.facebook.com/zabavnicentrumhornik', options)
    .text('Adresa: Zámecká 18, 702 00 Ostrava', options)
}

function generateGiftVoucher(doc, containerOption) {
  doc.font(boldText).text('DÁRKOVÝ POUKAZ - Chytrý a originální dárek k narozeninám',
    table3Width + table4width + 55 + doc.widthOfString('a'.repeat(20)), doc.page.height / 2, containerOption)
  doc.moveDown();
  doc.font(regularText).text('Poukazka lze využít na libovolnou aktivitu v ZC Horník', containerOption)
  doc.font(boldText).text('LASER GAME / VIRTUÁLNÍ REALITA / ARCHERY GAME', containerOption)
  doc.moveDown();
  doc.font(regularText).text('Více info na baru nebo webu', containerOption)
  doc.font(boldText).text('www.zabavahornik.cz', containerOption);
}

function generateMainTable(offset, length) {
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
  
  game.result.evaluationPlayers.slice(offset, length).forEach((p, index) => {
    const player = game.playersList.find(o => o.name === p.playerName);
    table.pushRow([
      `${index + offset + 1}.`,
      p.playerName,
      p.playerScore.toString(),
      (player && player.selectedTeam && game.selectedGameTemplate.teamGame &&  player.selectedTeam.name) || '',
      p.playerAmmo.toString(),
      p.playerKills.toString(),
      p.playerFootSteps ? p.playerFootSteps.toString() : '0',
      p.playerPrecision.toString() + ' %',
    ])
  });
  return table;
}

function generateHitsTable(offset, length, hits) {
  const players = game.result.evaluationPlayers.slice(offset, length)
  const table = new Table({
    paddingRight: 12,
    paddingLeft: 12,
    columnsNumber: game.result.evaluationPlayers.length + 1,
    xOffset: 20,
    yOffset: doc.page.height / 2  + 5,
    rotateHeader: true,
    boldColumn: [0],
  });
  table.pushRow([''].concat(game.result.evaluationPlayers.map((p, i) => {
    const t = `${i + 1}. ${p.playerName}`;
    if (t.length > 8) {
      return t.slice(0,7) + '...'
    }
    return t;
  })));
  
  players.forEach((p, index) => {
    const player = game.playersList.find(o => o.name === p.playerName);
    const array = [`${index + offset + 1}. ${p.playerName} ${(player && player.selectedTeam &&
    game.selectedGameTemplate.teamGame && player.selectedTeam.name) ?
    ' (' + player.selectedTeam.name + ')' : ''}`];
    game.result.evaluationPlayers.slice(0, 20).forEach((p2, index2) => {
      if (index !== index2) {
        const h_ = hits[index2].find(h => h.hitsWho === p.playerName);
        array.push(h_ ? (h_.hitsTotal || 0).toString() : '')
      } else {
        array.push('-')
      }
    })
    table.pushRow(array);  
  })
  
  return table;
}

function generateTeamTable(xOffSet) {
  const table = new Table({
    paddingRight: 12,
    paddingLeft: 12,
    columnsNumber: game.result.evaluationTeams.length + 1,
    xOffset: xOffSet,//table3Width + 40,
    yOffset: doc.page.height / 2 - 20,
    boldColumn: [1],
  });
  
  table.pushRow(['Tým', 'Skóre']);
  
  game.result.evaluationTeams.forEach(t => {
    table.pushRow([
      t.name,
      t.score.toString(),
    ])
  })
  return table;
}
